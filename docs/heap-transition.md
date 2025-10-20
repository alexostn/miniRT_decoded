# Architecture Transition: Stack to Heap (Full Migration)

**⚠️ This document describes a COMPLETE replacement of stack-based arrays with heap-based dynamic allocation from the start.**

For a hybrid approach (stack small objects, heap for overflow), see [Hybrid Heap Transition](hybrid-heap-transition.md).

---

This document shows the architectural changes needed when transitioning from fixed-size arrays (stack-based) to dynamic allocation (heap-based) for scalability.

## Current Architecture (Stack-based)

### World Structure (Fixed Arrays)
```c
// Current implementation
#define MAX_OBJECTS 100

typedef struct s_world
{
    t_sphere    spheres[MAX_OBJECTS];   // Fixed size array
    int         spheres_count;          // Current count
    t_light     light;                  // Single light
    // No capacity tracking needed
}   t_world;
```

**Pros:**
- Simple allocation: `t_world world = world_make();`
- No reallocation needed
- Predictable memory layout
- Fast access (contiguous memory)

**Cons:**
- Fixed limit (MAX_OBJECTS = 100)
- Wastes memory if few objects (100 * sizeof(t_sphere))
- Can't handle large scenes (>100 objects)
- Need to change MAX_OBJECTS and recompile

### Memory Layout Diagram

```
Stack Memory (Fixed Size):
┌─────────────────────────────────────────────────────────────┐
│ t_world world                                               │
│ ┌─────────────────────────────────────────────────────────┐ │
│ │ spheres[0]  │ 112 bytes (t_sphere)                     │ │
│ │ spheres[1]  │ 112 bytes                                │ │
│ │ spheres[2]  │ 112 bytes                                │ │
│ │ ...         │ ...                                      │ │
│ │ spheres[99] │ 112 bytes                                │ │ ← Allocated but unused
│ ├─────────────────────────────────────────────────────────┤ │
│ │ spheres_count: 3                                        │ │
│ │ light: { position, intensity, color }                   │ │
│ └─────────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────┘
Total: ~11,200 bytes allocated (but only ~350 bytes used for 3 spheres)
```

## Future Architecture (Heap-based)

### World Structure (Dynamic Arrays)
```c
// Future implementation
typedef struct s_world
{
    t_sphere    *spheres;       // Pointer to dynamic array
    int         spheres_count;  // Current count
    int         spheres_capacity; // Allocated capacity
    t_light     *lights;        // Dynamic array of lights
    int         lights_count;
    int         lights_capacity;
}   t_world;
```

**Pros:**
- Flexible capacity (grow as needed)
- Efficient memory usage (allocate only what's needed)
- No recompilation for larger scenes
- Support unlimited objects (within memory limits)

**Cons:**
- More complex allocation/deallocation
- Reallocation overhead when growing
- Need careful memory management
- Potential fragmentation

### Memory Layout Diagram

```
Heap Memory (Dynamic Growth):

Initial state (empty world):
┌──────────────────────────────────────┐
│ t_world world (stack)                │
│ ┌──────────────────────────────────┐ │
│ │ spheres: NULL                    │ │ ← No allocation yet
│ │ spheres_count: 0                 │ │
│ │ spheres_capacity: 0              │ │
│ └──────────────────────────────────┘ │
└──────────────────────────────────────┘

After first sphere (capacity = 4):
┌──────────────────────────────────────┐
│ t_world world (stack)                │
│ ┌──────────────────────────────────┐ │     Heap:
│ │ spheres: 0x1234 ────────────────────────> ┌────────────────┐
│ │ spheres_count: 1                 │ │      │ spheres[0] ✓   │ 112 bytes used
│ │ spheres_capacity: 4              │ │      │ spheres[1]     │ 112 bytes free
│ └──────────────────────────────────┘ │      │ spheres[2]     │ 112 bytes free
└──────────────────────────────────────┘      │ spheres[3]     │ 112 bytes free
                                               └────────────────┘
                                               Total: 448 bytes

After 4th sphere (need to grow):
┌──────────────────────────────────────┐
│ t_world world (stack)                │
│ ┌──────────────────────────────────┐ │     Old Heap:         New Heap:
│ │ spheres: 0x5678 ────────────────────────> [freed]          ┌────────────────┐
│ │ spheres_count: 5                 │ │                       │ spheres[0] ✓   │
│ │ spheres_capacity: 8              │ │                       │ spheres[1] ✓   │
│ └──────────────────────────────────┘ │                       │ spheres[2] ✓   │
└──────────────────────────────────────┘                       │ spheres[3] ✓   │
                                                                │ spheres[4] ✓   │
                                                                │ spheres[5]     │
                                                                │ spheres[6]     │
                                                                │ spheres[7]     │
                                                                └────────────────┘
                                                                Total: 896 bytes
```

## Transition Roadmap

### Phase 1: Preparation (Parser-Ready Code)
```c
// Current parser code is already heap-ready!
bool parse_sphere(char *line, t_scene *scene)
{
    // ... parsing logic ...
    
    // This function signature doesn't change
    return (world_add_sphere(&scene->world, sphere));
}
```

**Status**: ✅ DONE — Parser uses `world_add_sphere()` abstraction

### Phase 2: World Initialization Changes

**Current (Stack)**:
```c
t_world world_make(void)
{
    t_world world;
    
    world.spheres_count = 0;
    world.light = light_point(point(0, 0, 0), color(1, 1, 1));
    return (world);
}
```

**Future (Heap)**:
```c
t_world world_make(void)
{
    t_world world;
    
    world.spheres = NULL;
    world.spheres_count = 0;
    world.spheres_capacity = 0;
    world.lights = NULL;
    world.lights_count = 0;
    world.lights_capacity = 0;
    return (world);
}
```

### Phase 3: Add Sphere Changes

**Current (Stack)**:
```c
bool world_add_sphere(t_world *world, t_sphere sphere)
{
    if (!world)
        return (false);
    if (world->spheres_count >= MAX_OBJECTS)
        return (false);  // ← Hard limit
    world->spheres[world->spheres_count] = sphere;
    world->spheres_count++;
    return (true);
}
```

**Future (Heap)**:
```c
#define INITIAL_CAPACITY 4
#define GROWTH_FACTOR 2

bool world_add_sphere(t_world *world, t_sphere sphere)
{
    t_sphere *new_array;
    int new_capacity;
    
    if (!world)
        return (false);
    
    // Grow array if needed
    if (world->spheres_count >= world->spheres_capacity)
    {
        if (world->spheres_capacity == 0)
            new_capacity = INITIAL_CAPACITY;
        else
            new_capacity = world->spheres_capacity * GROWTH_FACTOR;
        
        new_array = realloc(world->spheres, 
                           sizeof(t_sphere) * new_capacity);
        if (!new_array)
            return (false);  // Out of memory
        
        world->spheres = new_array;
        world->spheres_capacity = new_capacity;
    }
    
    world->spheres[world->spheres_count] = sphere;
    world->spheres_count++;
    return (true);
}
```

### Phase 4: Cleanup Changes

**Current (Stack)**:
```c
// No cleanup needed for stack-based
void cleanup(t_data *data)
{
    // world.spheres is on stack, automatically freed
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    // ...
}
```

**Future (Heap)**:
```c
void free_world(t_world *world)
{
    if (!world)
        return;
    
    // Free dynamic arrays
    if (world->spheres)
    {
        free(world->spheres);
        world->spheres = NULL;
    }
    if (world->lights)
    {
        free(world->lights);
        world->lights = NULL;
    }
    
    world->spheres_count = 0;
    world->spheres_capacity = 0;
    world->lights_count = 0;
    world->lights_capacity = 0;
}

void cleanup(t_data *data)
{
    free_world(&data->scene.world);  // ← New: free heap allocations
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    // ...
}
```

## Memory Growth Comparison

### Stack-based (Current)
```
Objects:   0    1    2    3    4    5    ...   99   100
Memory: 11.2K 11.2K 11.2K 11.2K 11.2K 11.2K ... 11.2K [FAIL]
          ↑                                              ↑
     Allocated immediately                          Hard limit
```

### Heap-based (Future)
```
Objects:   0     1     2     3     4     5     8     9    16    17
Memory:    0  0.4K  0.4K  0.4K  0.4K  0.9K  0.9K  1.8K  1.8K  3.6K ...
           ↑    ↑                  ↑         ↑         ↑         ↑
         Start Alloc            Grow      Grow      Grow      Grow
         
Growth pattern: 0 → 4 → 8 → 16 → 32 → 64 → 128 → 256 → ...
```

## Call Stack Changes

### Current Stack Trace
```
main()
  → parse_scene_file()
     → parse_sphere()
        → world_add_sphere()  ← Simple array assignment
           → world->spheres[count] = sphere
```

### Future Stack Trace
```
main()
  → parse_scene_file()
     → parse_sphere()
        → world_add_sphere()
           ├─> [if full] realloc()  ← Potential growth
           │   └─> memcpy old → new
           └─> world->spheres[count] = sphere
  → cleanup()
     → free_world()  ← New: must free heap allocations
        └─> free(world->spheres)
```

## Error Handling

### Stack-based (Current)
```c
// Simple error: scene too large
if (world->spheres_count >= MAX_OBJECTS)
{
    parser_error("Too many spheres (max 100)", line_num);
    return (false);
}
```

### Heap-based (Future)
```c
// Graceful degradation: out of memory
if (!world_add_sphere(&world, sphere))
{
    parser_error("Out of memory while adding sphere", line_num);
    free_world(&world);  // Clean up partial scene
    return (false);
}
```

## Performance Considerations

### Stack-based
- **Allocation**: O(1) — pre-allocated at creation
- **Access**: O(1) — direct array indexing
- **Growth**: N/A — fixed size
- **Memory**: Always MAX_OBJECTS × sizeof(t_sphere)

### Heap-based
- **Allocation**: O(1) amortized — occasional realloc
- **Access**: O(1) — pointer dereference + indexing
- **Growth**: O(n) when growing (memcpy old → new)
- **Memory**: Only what's used + some overhead

### When to Grow (Doubling Strategy)
```
Capacity sequence: 4 → 8 → 16 → 32 → 64 → 128 → 256 → ...

Reallocations for 100 objects:
  Stack: 1 allocation (100 × 112 bytes = 11.2 KB)
  Heap:  7 reallocations total
    1st: NULL → 4 items
    2nd: 4 → 8 items
    3rd: 8 → 16 items
    4th: 16 → 32 items
    5th: 32 → 64 items
    6th: 64 → 128 items
    Final: 128 items (28 free) = 14.3 KB
```

## Testing Strategy

### Unit Tests
```c
void test_world_growth(void)
{
    t_world world = world_make();
    t_sphere sphere = sphere_create();
    
    // Add beyond initial capacity
    for (int i = 0; i < 10; i++)
    {
        assert(world_add_sphere(&world, sphere) == true);
        assert(world.spheres_count == i + 1);
    }
    
    // Verify capacity grew
    assert(world.spheres_capacity >= 10);
    
    free_world(&world);
}
```

### Memory Leak Tests
```bash
# Must pass with 0 leaks after transition
valgrind --leak-check=full ./miniRT large_scene.rt
```

## Migration Checklist

- [ ] Update `t_world` structure (add capacity fields, pointers)
- [ ] Implement `world_make()` with NULL initialization
- [ ] Implement `world_add_sphere()` with realloc logic
- [ ] Implement `world_add_light()` (new: multiple lights)
- [ ] Implement `free_world()` cleanup function
- [ ] Update all callers to use `free_world()`
- [ ] Add error handling for malloc/realloc failures
- [ ] Update tests to verify growth behavior
- [ ] Run Valgrind to ensure no leaks
- [ ] Update documentation

## See Also
- [Architecture Comparison](architecture-comparison.md) — **Read first:** detailed benchmark stack vs heap vs hybrid
- [Hybrid Heap Transition](hybrid-heap-transition.md) — **Alternative approach**: stack for small scenes, heap for overflow
- [Hybrid Architecture Flowchart](hybrid-architecture-flowchart.md) — visual diagrams for hybrid
- [Memory Management](memory-management.md) — Leak detection and cleanup
- [Parser Components](parser/05-components.md) — Module structure
- [Parser Call Tree](parser/06-calltree.md) — Function hierarchy

---

*Note: This is a FULL MIGRATION approach. Current implementation uses stack-based arrays (MAX_OBJECTS = 100). For hybrid stack+heap approach, see [hybrid-heap-transition.md](hybrid-heap-transition.md).*
