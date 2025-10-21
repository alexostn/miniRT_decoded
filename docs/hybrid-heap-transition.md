# Hybrid Heap Transition Plan

**Strategy:** Start with embedded stack array (fast for small scenes), migrate to heap only when needed (flexible for large scenes).

**Key Feature:** ⚙️ **Configurable HEAP_THRESHOLD** — easily tune stack→heap boundary in one place, or disable heap entirely for pure stack mode.

---

## Configuration Design (Single Point of Control)

### Master Configuration File

**File:** `include/memory_config.h` (new file)

```c
#ifndef MEMORY_CONFIG_H
# define MEMORY_CONFIG_H

/* ========================================================================
 * MEMORY ARCHITECTURE CONFIGURATION
 * ======================================================================== */

/* Strategy Selection:
 *   STRATEGY_STACK  - Fixed array (no heap, simple)
 *   STRATEGY_HEAP   - Dynamic from start (unlimited)
 *   STRATEGY_HYBRID - Stack for small, heap for large (recommended)
 */
# define STRATEGY_HYBRID

/* Heap Threshold: Objects that fit in stack before migrating to heap
 * Common values:
 *   8  - Conservative (less dead weight after migration)
 *   16 - Balanced (recommended for miniRT)
 *   32 - Aggressive (optimize for small scenes)
 */
# define HEAP_THRESHOLD 16

/* Heap Growth Strategy (only for STRATEGY_HEAP or STRATEGY_HYBRID) */
# define HEAP_INITIAL_CAPACITY (HEAP_THRESHOLD * 2)  // 32 for threshold=16
# define HEAP_GROWTH_FACTOR 2                        // Double on growth

/* Pure Stack Configuration (only for STRATEGY_STACK) */
# define MAX_OBJECTS 100

#endif
```

**Benefits:**
- ✅ Change `HEAP_THRESHOLD` in **one place**
- ✅ Switch strategies with `#ifdef` (no code changes)
- ✅ Easy to experiment: try 8, 16, 32 and benchmark

---

## Modular Code Organization

### Directory Structure (Heap Code Isolated)

```
src/
├── world/
│   ├── world_common.c          # Common functions (both stack/heap)
│   ├── world_stack.c           # Pure stack implementation
│   └── heap/                   # ← HEAP MODULE (can be deleted!)
│       ├── world_heap.c        # Pure heap implementation
│       ├── world_hybrid.c      # Hybrid implementation
│       ├── heap_migrate.c      # Migration logic
│       └── heap_grow.c         # Realloc logic
│
include/
├── memory_config.h             # ⚙️ Configuration (HEAP_THRESHOLD)
├── world.h                     # Public API (strategy-agnostic)
└── world_internal.h            # Internal (includes strategy-specific)
```

**To get pure stack version:**
1. Delete `src/world/heap/` directory	
2. Change `memory_config.h`: `#define STRATEGY_STACK`
3. Recompile → **No heap code included!**

---

## Strategy-Specific Structure Definitions

**File:** `include/world.h`

```c
#include "memory_config.h"

/* Strategy-specific world structure */
#ifdef STRATEGY_STACK

typedef struct s_world
{
    t_sphere    spheres[MAX_OBJECTS];
    int         spheres_count;
    t_light     light;
}   t_world;

#elif defined(STRATEGY_HEAP)

typedef struct s_world
{
    t_sphere    *spheres;
    int         spheres_count;
    int         spheres_capacity;
    t_light     light;
}   t_world;

#elif defined(STRATEGY_HYBRID)

typedef struct s_world
{
    t_sphere    stack_spheres[HEAP_THRESHOLD];  // Embedded
    t_sphere    *heap_spheres;                   // Dynamic
    int         spheres_count;
    int         heap_capacity;
    bool        using_heap;
    t_light     light;
}   t_world;

#else
# error "Must define STRATEGY_STACK, STRATEGY_HEAP, or STRATEGY_HYBRID"
#endif

/* Public API (same for all strategies) */
t_world world_make(void);
bool    world_add_sphere(t_world *world, t_sphere sphere);
t_sphere* world_get_sphere(t_world *world, int index);
void    free_world(t_world *world);
```

**Benefit:** Parser code **unchanged** regardless of strategy!

## Architecture Overview

### Hybrid Structure Design

```c
#define STACK_CAPACITY 16  // Embedded array size (tunable)

typedef struct s_world
{
    // Embedded stack storage (always allocated)
    t_sphere    stack_spheres[STACK_CAPACITY];
    
    // Heap overflow storage (allocated on demand)
    t_sphere    *heap_spheres;
    int         heap_capacity;
    
    // Shared counters
    int         spheres_count;     // Total count (stack + heap)
    bool        using_heap;        // Mode flag
    
    // Lights (can use same hybrid strategy)
    t_light     light;  // Keep simple for now
}   t_world;
```

**Key Invariants:**
- `spheres_count <= STACK_CAPACITY` → all objects in `stack_spheres[]`
- `spheres_count > STACK_CAPACITY` → first 16 in `heap_spheres[]`, rest also in `heap_spheres[]`
- `using_heap = false` → `heap_spheres = NULL`, `heap_capacity = 0`
- `using_heap = true` → `heap_spheres != NULL`, `heap_capacity >= spheres_count`

### Memory Layout States

```
State 1: Empty (0 objects)
┌────────────────────────────────────────┐
│ t_world (stack)                        │
│ ┌────────────────────────────────────┐ │
│ │ stack_spheres[16]  (1.8 KB)       │ │ ← Embedded, always here
│ │ heap_spheres: NULL                 │ │
│ │ spheres_count: 0                   │ │
│ │ heap_capacity: 0                   │ │
│ │ using_heap: false                  │ │
│ └────────────────────────────────────┘ │
└────────────────────────────────────────┘

State 2: Small Scene (10 objects)
┌────────────────────────────────────────┐
│ t_world (stack)                        │
│ ┌────────────────────────────────────┐ │
│ │ stack_spheres[0-9]: ✓ (used)      │ │
│ │ stack_spheres[10-15]: (unused)     │ │
│ │ heap_spheres: NULL                 │ │ ← No heap yet
│ │ spheres_count: 10                  │ │
│ │ heap_capacity: 0                   │ │
│ │ using_heap: false                  │ │
│ └────────────────────────────────────┘ │
└────────────────────────────────────────┘

State 3: Migration (17th object triggers)
┌────────────────────────────────────────┐
│ t_world (stack)                        │     Heap:
│ ┌────────────────────────────────────┐ │     ┌──────────────────┐
│ │ stack_spheres[16]: (old data)      │ │     │ heap[0-15]: ✓    │ ← Copied
│ │ heap_spheres: 0x1234 ──────────────┼─┼────>│ heap[16]: ✓      │ ← New 17th
│ │ spheres_count: 17                  │ │     │ heap[17-31]: free│
│ │ heap_capacity: 32                  │ │     └──────────────────┘
│ │ using_heap: true                   │ │
│ └────────────────────────────────────┘ │
└────────────────────────────────────────┘
Note: stack_spheres[] data is now stale, but still occupies memory

State 4: Large Scene (50 objects)
┌────────────────────────────────────────┐
│ t_world (stack)                        │     Heap:
│ ┌────────────────────────────────────┐ │     ┌──────────────────┐
│ │ stack_spheres[16]: (stale)         │ │     │ heap[0-49]: ✓    │
│ │ heap_spheres: 0x5678 ──────────────┼─┼────>│ heap[50-63]: free│
│ │ spheres_count: 50                  │ │     └──────────────────┘
│ │ heap_capacity: 64                  │ │     (reallocated 32→64)
│ │ using_heap: true                   │ │
│ └────────────────────────────────────┘ │
└────────────────────────────────────────┘
```

## Implementation Roadmap

### Phase 1: Structure Update

**File:** `include/memory_config.h` (NEW)

Create central configuration:

```c
#ifndef MEMORY_CONFIG_H
# define MEMORY_CONFIG_H

# define STRATEGY_HYBRID      // Active strategy
# define HEAP_THRESHOLD 16    // ⚙️ Tune here!
# define HEAP_INITIAL_CAPACITY (HEAP_THRESHOLD * 2)
# define HEAP_GROWTH_FACTOR 2

#endif
```

**File:** `include/world.h`

Update structure with conditional compilation:

```c
#include "memory_config.h"

#ifdef STRATEGY_HYBRID

typedef struct s_world
{
    t_sphere    stack_spheres[HEAP_THRESHOLD];  // ← Uses config value
    t_sphere    *heap_spheres;
    int         spheres_count;
    int         heap_capacity;
    bool        using_heap;
    t_light     light;
}   t_world;

#endif
```

**Changes:**
- ✅ `HEAP_THRESHOLD` replaces hardcoded `16`
- ✅ Structure size adapts automatically (8 → 896B, 16 → 1.8KB, 32 → 3.6KB)
- ✅ Easy to test different values

### Phase 2: Initialization

**File:** `src/world/world_init.c` (or similar)

```c
t_world world_make(void)
{
    t_world world;
    
    // Initialize embedded stack storage
    // (stack_spheres[] allocated automatically as part of world struct)
    
    // Initialize heap storage (starts NULL)
    world.heap_spheres = NULL;
    world.heap_capacity = 0;
    
    // Counters
    world.spheres_count = 0;
    
    // Start in stack mode
    world.using_heap = false;
    
    // Default light
    world.light = light_point(point(0, 0, 0), color(1, 1, 1));
    
    return (world);
}
```

**Testing:**
```c
void test_world_init(void)
{
    t_world world = world_make();
    
    assert(world.spheres_count == 0);
    assert(world.heap_spheres == NULL);
    assert(world.heap_capacity == 0);
    assert(world.using_heap == false);
}
```

### Phase 3: Add Sphere (Core Logic)

**File:** `src/world/heap/world_hybrid.c` (NEW — isolates heap logic!)

```c
#include "memory_config.h"

#ifdef STRATEGY_HYBRID

/* Helper: Migrate from stack to heap (in heap/ directory) */
static bool migrate_to_heap(t_world *world, t_sphere new_sphere)
{
    t_sphere *new_array;
    int new_capacity;
    
    // Allocate using configured capacity
    new_capacity = HEAP_INITIAL_CAPACITY;  // From config (32 if threshold=16)
    new_array = malloc(sizeof(t_sphere) * new_capacity);
    if (!new_array)
        return (false);
    
    // Copy all stack objects to heap
    ft_memcpy(new_array, world->stack_spheres, 
              sizeof(t_sphere) * HEAP_THRESHOLD);  // ← Uses config
    
    // Add the new sphere that triggered migration
    new_array[HEAP_THRESHOLD] = new_sphere;
    
    // Update world structure
    world->heap_spheres = new_array;
    world->heap_capacity = new_capacity;
    world->spheres_count = HEAP_THRESHOLD + 1;
    world->using_heap = true;
    
    return (true);
}

/* Helper: Grow heap array */
static bool grow_heap(t_world *world)
{
    t_sphere *new_array;
    int new_capacity;
    
    new_capacity = world->heap_capacity * HEAP_GROWTH_FACTOR;  // ← From config
    new_array = realloc(world->heap_spheres, 
                        sizeof(t_sphere) * new_capacity);
    if (!new_array)
        return (false);
    
    world->heap_spheres = new_array;
    world->heap_capacity = new_capacity;
    return (true);
}

/* Main function */
bool world_add_sphere(t_world *world, t_sphere sphere)
{
    if (!world)
        return (false);
    
    // Case 1: Using stack mode
    if (!world->using_heap)
    {
        // Check if still fits in stack
        if (world->spheres_count < HEAP_THRESHOLD)  // ← Config-based
        {
            world->stack_spheres[world->spheres_count] = sphere;
            world->spheres_count++;
            return (true);
        }
        
        // Stack full → trigger migration
        return (migrate_to_heap(world, sphere));
    }
    
    // Case 2: Using heap mode
    else
    {
        // Check if heap needs to grow
        if (world->spheres_count >= world->heap_capacity)
        {
            if (!grow_heap(world))
                return (false);
        }
        
        world->heap_spheres[world->spheres_count] = sphere;
        world->spheres_count++;
        return (true);
    }
}

#endif /* STRATEGY_HYBRID */
```

**Key Benefits:**
1. All heap code in `src/world/heap/` directory
2. `HEAP_THRESHOLD` used throughout (no hardcoded 16)
3. Delete `heap/` folder → no heap code compiled
4. `#ifdef STRATEGY_HYBRID` → only active if configured

### Phase 4: Access Sphere

**File:** `src/world/world_get_sphere.c`

```c
t_sphere* world_get_sphere(t_world *world, int index)
{
    if (!world || index < 0 || index >= world->spheres_count)
        return (NULL);
    
    // Access based on current mode
    if (world->using_heap)
        return (&world->heap_spheres[index]);
    else
        return (&world->stack_spheres[index]);
}
```

**Alternative: Macro for inline access**
```c
// In header file
#define WORLD_GET_SPHERE(world, i) \
    ((world)->using_heap ? &(world)->heap_spheres[i] : &(world)->stack_spheres[i])
```

### Phase 5: Cleanup

**File:** `src/world/world_cleanup.c`

```c
void free_world(t_world *world)
{
    if (!world)
        return;
    
    // Free heap array if allocated
    if (world->using_heap && world->heap_spheres)
    {
        free(world->heap_spheres);
        world->heap_spheres = NULL;
    }
    
    // Reset counters
    world->spheres_count = 0;
    world->heap_capacity = 0;
    world->using_heap = false;
    
    // Note: stack_spheres[] freed automatically with world struct
}
```

**Update main cleanup:**
```c
void cleanup(t_data *data)
{
    free_world(&data->scene.world);  // Free heap if used
    
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    // ... rest of cleanup
}
```

## Migration Behavior

### Capacity Growth Pattern

```
Objects:  0-16    17     18-32   33     34-64   65     66-128  129
Mode:     Stack   Heap   Heap    Heap   Heap    Heap   Heap    Heap
Capacity: 16      32     32      64     64      128    128     256
Action:   Add     Migrate Add    Realloc Add    Realloc Add    Realloc
```

### Memory Overhead

```
Stack storage: 16 * 112 bytes = 1,792 bytes (always present)
Heap storage:  capacity * 112 bytes (when using_heap = true)

Examples:
  10 objects: 1,792 bytes (stack only)
  17 objects: 1,792 + (32 * 112) = 5,376 bytes
  50 objects: 1,792 + (64 * 112) = 8,960 bytes
  
Note: Stack storage becomes "dead weight" after migration,
      but it's only 1.8 KB so acceptable overhead.
```

### Performance Characteristics

| Operation | Stack Mode (0-16) | Heap Mode (17+) |
|-----------|-------------------|-----------------|
| Add (typical) | O(1) | O(1) amortized |
| Add (migration) | — | O(n) — one time at 17th object |
| Add (growth) | — | O(n) — when doubling capacity |
| Access | O(1) — direct array | O(1) — pointer + index |
| Memory | 1.8 KB fixed | 1.8 KB + dynamic |

## Error Handling

### Stack Mode Errors

```c
// No errors possible in stack mode (0-16 objects)
// Array is pre-allocated
if (world->spheres_count < STACK_CAPACITY)
{
    world->stack_spheres[world->spheres_count++] = sphere;
    return (true);  // Always succeeds
}
```

### Migration Errors

```c
// Migration can fail due to malloc failure
if (!migrate_to_heap(world, sphere))
{
    // Parser error handling
    parser_error("Out of memory migrating to heap", line_num);
    return (false);  // Scene parsing failed
}
```

### Heap Growth Errors

```c
// Realloc can fail
if (!grow_heap(world))
{
    parser_error("Out of memory growing heap", line_num);
    return (false);
}
```

## Testing Strategy

### Unit Tests

```c
// Test 1: Small scene (stack only)
void test_hybrid_stack_only(void)
{
    t_world world = world_make();
    t_sphere sphere = sphere_create();
    
    for (int i = 0; i < 10; i++)
        assert(world_add_sphere(&world, sphere) == true);
    
    assert(world.spheres_count == 10);
    assert(world.using_heap == false);
    assert(world.heap_spheres == NULL);
    
    free_world(&world);
}

// Test 2: Exact stack boundary (16 objects)
void test_hybrid_stack_full(void)
{
    t_world world = world_make();
    t_sphere sphere = sphere_create();
    
    for (int i = 0; i < 16; i++)
        assert(world_add_sphere(&world, sphere) == true);
    
    assert(world.spheres_count == 16);
    assert(world.using_heap == false);  // Still stack
    
    free_world(&world);
}

// Test 3: Migration trigger (17th object)
void test_hybrid_migration(void)
{
    t_world world = world_make();
    t_sphere sphere = sphere_create();
    
    for (int i = 0; i < 17; i++)
        assert(world_add_sphere(&world, sphere) == true);
    
    assert(world.spheres_count == 17);
    assert(world.using_heap == true);       // Migrated!
    assert(world.heap_spheres != NULL);
    assert(world.heap_capacity == 32);
    
    free_world(&world);
}

// Test 4: Large scene (heap growth)
void test_hybrid_heap_growth(void)
{
    t_world world = world_make();
    t_sphere sphere = sphere_create();
    
    for (int i = 0; i < 50; i++)
        assert(world_add_sphere(&world, sphere) == true);
    
    assert(world.spheres_count == 50);
    assert(world.using_heap == true);
    assert(world.heap_capacity == 64);  // Grew from 32
    
    free_world(&world);
}

// Test 5: Access correctness
void test_hybrid_access(void)
{
    t_world world = world_make();
    
    // Add 20 objects with unique IDs
    for (int i = 0; i < 20; i++)
    {
        t_sphere sphere = sphere_create();
        sphere.id = i;  // Assuming ID field
        world_add_sphere(&world, sphere);
    }
    
    // Verify access works in both modes
    for (int i = 0; i < 20; i++)
    {
        t_sphere *s = world_get_sphere(&world, i);
        assert(s != NULL);
        assert(s->id == i);
    }
    
    free_world(&world);
}
```

### Memory Leak Tests

```bash
# Test small scene (stack only, no leaks)
valgrind --leak-check=full ./miniRT small_scene.rt
# Expected: 0 leaks (no heap used)

# Test medium scene (migration, should free heap)
valgrind --leak-check=full ./miniRT medium_scene.rt
# Expected: 0 leaks (heap properly freed)

# Test large scene (heap growth, should free all)
valgrind --leak-check=full ./miniRT large_scene.rt
# Expected: 0 leaks (all reallocs freed)
```

## Advantages of Hybrid Approach

### ✅ Pros

1. **Fast for small scenes** (most common use case)
   - No malloc for ≤16 objects
   - No free needed if stack-only
   - Cache-friendly contiguous memory

2. **Scales for large scenes**
   - Unlimited capacity (within memory)
   - Efficient growth (doubling strategy)

3. **Predictable performance**
   - Small scenes: O(1) add, no allocation overhead
   - Large scenes: amortized O(1) add

4. **Memory efficient**
   - Only 1.8 KB overhead for embedded array
   - Stack overhead negligible compared to heap savings

### ⚠️ Cons

1. **More complex code**
   - Need to manage two arrays
   - Access requires flag check
   - Migration logic adds complexity

2. **Dead stack storage after migration**
   - 1.8 KB wasted after 17th object
   - Not reclaimed (embedded in struct)

3. **One-time migration cost**
   - O(n) copy at 17th object (n=16)
   - Adds ~2 μs latency (negligible)

4. **Tuning required**
   - STACK_CAPACITY must be chosen carefully
   - Too small: frequent migrations
   - Too large: wasted memory

## Tuning HEAP_THRESHOLD

### How to Choose the Right Value

**Step 1:** Analyze your scene sizes

```bash
# Count objects in all .rt files
find scenes/ -name "*.rt" -exec grep -c "^sp\|^pl\|^cy" {} \; | sort -n | uniq -c

# Example output:
#   50 files with 3 objects
#   30 files with 5 objects
#   15 files with 10 objects
#    3 files with 20 objects
#    2 files with 50 objects
```

**Step 2:** Calculate coverage

```
If 80% of scenes have ≤8 objects:  → HEAP_THRESHOLD = 8  (conservative)
If 80% of scenes have ≤16 objects: → HEAP_THRESHOLD = 16 (balanced)
If 80% of scenes have ≤32 objects: → HEAP_THRESHOLD = 32 (aggressive)
```

**Step 3:** Edit `include/memory_config.h`

```c
// Change this ONE line:
#define HEAP_THRESHOLD 16  // Your chosen value
```

**Step 4:** Recompile and benchmark

```bash
make re
time ./miniRT scenes/*.rt  # Test performance
valgrind --leak-check=full ./miniRT test.rt  # Verify no leaks
```

---

### Recommendations by Use Case

```c
// Conservative (minimize dead weight)
#define HEAP_THRESHOLD 8   // 896 bytes embedded
// Use if: Memory is tight, scenes vary widely

// Balanced (recommended for miniRT)
#define HEAP_THRESHOLD 16  // 1.8 KB embedded ✅
// Use if: Typical 42 school project (3-20 objects)

// Aggressive (maximize stack usage)
#define HEAP_THRESHOLD 32  // 3.6 KB embedded
// Use if: Most scenes < 30 objects, performance critical

// Extreme (mostly large scenes)
#define HEAP_THRESHOLD 64  // 7.2 KB embedded
// Use if: Most scenes 50+ objects (or just use pure heap!)
```

---

### Memory Impact Table

| HEAP_THRESHOLD | Stack Size | Dead Weight (if migrated) | Covers X% Scenes |
|----------------|------------|---------------------------|------------------|
| 4              | 448 B      | 448 B                     | ~40% (too small) |
| 8              | 896 B      | 896 B                     | ~60%             |
| **16**         | **1.8 KB** | **1.8 KB**                | **~80%** ✅      |
| 32             | 3.6 KB     | 3.6 KB                    | ~95%             |
| 64             | 7.2 KB     | 7.2 KB                    | ~99% (overkill)  |

**Recommendation:** Start with **16**, profile, then adjust if needed.

## Switching to Pure Stack Mode

### Quick Disable of Heap Module

**Goal:** Get pure stack implementation without heap complexity

**Step 1:** Edit `include/memory_config.h`

```c
// Change from:
// #define STRATEGY_HYBRID

// To:
#define STRATEGY_STACK
#define MAX_OBJECTS 100  // Or your desired limit
```

**Step 2:** (Optional) Delete heap code

```bash
# Remove heap implementation directory
rm -rf src/world/heap/

# Or just exclude from compilation in Makefile:
# SRCS := $(filter-out src/world/heap/%, $(SRCS))
```

**Step 3:** Recompile

```bash
make fclean
make
```

**Result:**
- ✅ No heap code compiled
- ✅ Simple `t_sphere spheres[MAX_OBJECTS]` structure
- ✅ No malloc/free logic
- ✅ Smaller binary size

**Use Case:** If you determine hybrid is overkill for your needs.

---

## Migration Checklist (with Modularity)

### File Structure Setup
- [ ] Create `include/memory_config.h` with HEAP_THRESHOLD
- [ ] Create `src/world/heap/` directory for heap-specific code
- [ ] Update `include/world.h` with strategy-based #ifdef
- [ ] Update Makefile to conditionally compile heap/ files

### Implementation
- [ ] Implement `world_make()` in `src/world/world_common.c`
- [ ] Implement `migrate_to_heap()` in `src/world/heap/heap_migrate.c`
- [ ] Implement `grow_heap()` in `src/world/heap/heap_grow.c`
- [ ] Implement `world_add_sphere()` in `src/world/heap/world_hybrid.c`
- [ ] Implement `world_get_sphere()` with mode check
- [ ] Implement `free_world()` in cleanup (check using_heap flag)

### Testing
- [ ] Test pure stack mode (STRATEGY_STACK)
- [ ] Test pure heap mode (STRATEGY_HEAP)
- [ ] Test hybrid with HEAP_THRESHOLD=8, 16, 32
- [ ] Unit test: 0-15 objects (stack only)
- [ ] Unit test: exactly 16 objects (boundary)
- [ ] Unit test: 17 objects (migration trigger)
- [ ] Unit test: 50+ objects (heap growth)
- [ ] Valgrind: no leaks for all modes
- [ ] Benchmark: compare stack vs heap vs hybrid

### Tuning
- [ ] Profile scene size distribution
- [ ] Choose optimal HEAP_THRESHOLD
- [ ] Document choice in config file
- [ ] Re-benchmark after tuning

### Cleanup (Optional)
- [ ] Remove heap/ directory if using pure stack
- [ ] Update documentation with chosen strategy
- [ ] Commit final configuration to version control

## Comparison with Alternatives

| Approach | Memory (10 obj) | Memory (100 obj) | Complexity | Best For |
|----------|-----------------|------------------|------------|----------|
| **Pure Stack** | 11.2 KB | FAIL | Low | Fixed limits OK |
| **Pure Heap** | ~1 KB | ~14 KB | Medium | Unlimited scenes |
| **Hybrid** | 1.8 KB | ~14 KB | High | Most common: small scenes, some large |

## See Also
- [Architecture Comparison](architecture-comparison.md) — **Read first:** Why hybrid? Detailed benchmarks
- [Hybrid Architecture Flowchart](hybrid-architecture-flowchart.md) — Visual flow diagrams
- [Full Heap Migration](heap-transition.md) — Alternative approach (pure heap)
- [Memory Management](memory-management.md) — Leak debugging

---

*Hybrid heap transition plan for miniRT. Optimized for common case (small scenes) while supporting edge cases (large scenes). Configure `HEAP_THRESHOLD` to tune behavior.*
