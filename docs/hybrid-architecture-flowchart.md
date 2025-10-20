# Hybrid Architecture Flowchart

**Concept:** Use embedded stack array for small objects, transition to heap only when needed.

**Key Feature:** ⚙️ **Configurable HEAP_THRESHOLD** — tune the stack→heap boundary in `include/memory_config.h` (see [Hybrid Heap Transition](hybrid-heap-transition.md) for details).

---

## Configuration

```c
// include/memory_config.h
#define HEAP_THRESHOLD 16  // ⚙️ Change this to tune behavior
```

**Impact:**
- `HEAP_THRESHOLD = 8` → migrate at 9th object
- `HEAP_THRESHOLD = 16` → migrate at 17th object (default)
- `HEAP_THRESHOLD = 32` → migrate at 33rd object

All diagrams below use **HEAP_THRESHOLD** as the boundary value.

## High-Level Flow

```mermaid
graph TD
    Start([Program Start]) --> Init[Initialize World]
    Init --> |using_heap = false| StackMode[Stack Mode]
    
    StackMode --> AddObj{Add Object?}
    AddObj --> |Yes| CheckCount{Count < HEAP_THRESHOLD?}
    
    CheckCount --> |Yes| AddStack[Add to stack_spheres array]
    AddStack --> StackMode
    
    CheckCount --> |No| Migrate[Migration Triggered]
    Migrate --> AllocHeap[Allocate heap array]
    AllocHeap --> CopyData[Copy stack → heap]
    CopyData --> SetFlag[using_heap = true]
    SetFlag --> HeapMode[Heap Mode]
    
    HeapMode --> AddObj2{Add Object?}
    AddObj2 --> |Yes| CheckCap{Count < capacity?}
    
    CheckCap --> |Yes| AddHeap[Add to heap_spheres]
    AddHeap --> HeapMode
    
    CheckCap --> |No| Realloc[Realloc heap array]
    Realloc --> |Success| AddHeap
    Realloc --> |Fail| Error[Out of Memory]
    
    AddObj --> |No| Render[Render Scene]
    AddObj2 --> |No| Render
    
    Render --> Cleanup{Cleanup?}
    Cleanup --> |using_heap?| FreeHeap[Free heap_spheres]
    Cleanup --> |stack only| NoFree[No free needed]
    
    FreeHeap --> End([Program End])
    NoFree --> End
    Error --> End
    
    style Start fill:#90EE90
    style End fill:#FFB6C1
    style Migrate fill:#FFD700
    style Error fill:#FF6B6B
    style StackMode fill:#87CEEB
    style HeapMode fill:#DDA0DD
```

## Detailed Add Object Flow

```mermaid
flowchart TD
    AddSphere[world_add_sphere called] --> IsHeap{using_heap?}
    
    IsHeap --> |false| StackPath[Stack Path]
    IsHeap --> |true| HeapPath[Heap Path]
    
    StackPath --> StackFull{count >= HEAP_THRESHOLD?}
    
    StackFull --> |No| AddToStack[stack_spheres count++ = sphere]
    AddToStack --> ReturnOK[return true]
    
    StackFull --> |Yes| TriggerMigration[MIGRATION PHASE]
    
    TriggerMigration --> CalcNewCap[new_capacity = 32]
    CalcNewCap --> MallocHeap[malloc heap array]
    MallocHeap --> CheckMalloc{Success?}
    
    CheckMalloc --> |No| ReturnFail[return false]
    CheckMalloc --> |Yes| CopyLoop[memcpy stack → heap]
    
    CopyLoop --> UpdatePtr[heap_spheres = new array]
    UpdatePtr --> SetUsing[using_heap = true]
    SetUsing --> AddToHeap1[heap_spheres count++ = sphere]
    AddToHeap1 --> ReturnOK
    
    HeapPath --> HeapFull{count >= capacity?}
    
    HeapFull --> |No| AddToHeap2[heap_spheres count++ = sphere]
    AddToHeap2 --> ReturnOK
    
    HeapFull --> |Yes| GrowHeap[Realloc Growth Phase]
    
    GrowHeap --> CalcGrow[new_capacity = capacity * 2]
    CalcGrow --> ReallocCall[realloc heap array]
    ReallocCall --> CheckRealloc{Success?}
    
    CheckRealloc --> |No| ReturnFail
    CheckRealloc --> |Yes| UpdatePtr2[heap_spheres = reallocated]
    UpdatePtr2 --> AddToHeap3[heap_spheres count++ = sphere]
    AddToHeap3 --> ReturnOK
    
    style TriggerMigration fill:#FFD700,stroke:#FF8C00,stroke-width:3px
    style GrowHeap fill:#DDA0DD,stroke:#9370DB,stroke-width:3px
    style ReturnFail fill:#FF6B6B
    style ReturnOK fill:#90EE90
```

## Access Pattern Flow

```mermaid
flowchart LR
    Access[Access sphere i] --> CheckFlag{using_heap?}
    
    CheckFlag --> |false| StackAccess[return stack_spheres i]
    CheckFlag --> |true| HeapAccess[return heap_spheres i]
    
    StackAccess --> ValidateStack{i < count?}
    HeapAccess --> ValidateHeap{i < count?}
    
    ValidateStack --> |Yes| ReturnStack[Valid Access]
    ValidateStack --> |No| ErrorStack[Out of Bounds]
    
    ValidateHeap --> |Yes| ReturnHeap[Valid Access]
    ValidateHeap --> |No| ErrorHeap[Out of Bounds]
    
    style CheckFlag fill:#FFD700
    style ErrorStack fill:#FF6B6B
    style ErrorHeap fill:#FF6B6B
    style ReturnStack fill:#90EE90
    style ReturnHeap fill:#90EE90
```

## Memory State Transitions

```mermaid
stateDiagram-v2
    [*] --> StackOnly: Initialize
    
    state StackOnly {
        [*] --> Empty
        Empty --> Filling: Add objects
        Filling --> Filling: count++
        Filling --> Full: count = 16
    }
    
    StackOnly --> Migration: Add 17th object
    
    state Migration {
        [*] --> Allocating
        Allocating --> Copying: malloc success
        Copying --> Switching: memcpy done
        Switching --> [*]: using_heap = true
    }
    
    Migration --> HeapActive: Migration complete
    
    state HeapActive {
        [*] --> UsingHeap
        UsingHeap --> Growing: capacity full
        Growing --> UsingHeap: realloc done
    }
    
    HeapActive --> [*]: Cleanup (free heap)
    StackOnly --> [*]: Cleanup (no free)
    
    note right of StackOnly
        Memory: 16 * sizeof(t_sphere)
        Always allocated (embedded)
    end note
    
    note right of HeapActive
        Memory: capacity * sizeof(t_sphere)
        Dynamically grows: 32→64→128...
    end note
```

## Decision Points

### When to use Stack vs Heap?

```mermaid
flowchart TD
    Decision{Scene Size}
    
    Decision --> |≤ HEAP_THRESHOLD| UseStack[Use Stack Only]
    Decision --> |> HEAP_THRESHOLD| UseHeap[Migrate to Heap]
    
    UseStack --> Benefit1[✅ No malloc]
    UseStack --> Benefit2[✅ No free needed]
    UseStack --> Benefit3[✅ Fast access]
    UseStack --> Benefit4[✅ Cache-friendly]
    
    UseHeap --> Benefit5[✅ Unlimited capacity]
    UseHeap --> Benefit6[✅ Memory efficient for large scenes]
    
    Benefit1 --> Trade1[⚠️ Wastes 16*112 bytes if empty]
    Benefit5 --> Trade2[⚠️ One-time migration cost]
    
    style UseStack fill:#87CEEB
    style UseHeap fill:#DDA0DD
    style Decision fill:#FFD700
```

## Comparison: Stack, Heap, Hybrid

```mermaid
graph LR
    subgraph Pure Stack
        S1[Fixed Array 100]
        S2[Always 11.2 KB]
        S3[Hard Limit]
    end
    
    subgraph Pure Heap
        H1[Dynamic from start]
        H2[Grows: 0→4→8→16...]
        H3[Unlimited]
    end
    
    subgraph Hybrid
        HY1[Stack: 0-16 objects]
        HY2[Heap: 17+ objects]
        HY3[Best of Both]
    end
    
    Pure Stack --> |✅ Simple| Trade1[❌ Wastes memory]
    Pure Heap --> |✅ Flexible| Trade2[❌ Malloc overhead]
    Hybrid --> |✅ Fast small scenes| Trade3[❌ More complex code]
    
    style Hybrid fill:#FFD700,stroke:#FF8C00,stroke-width:3px
```

## Performance Characteristics

### Memory Usage Comparison (Objects → Memory)

```
Objects:    0      5      10     T      T+1    20     30     50     100
                                 ↓      ↓                            
Stack:    11.2K  11.2K  11.2K  11.2K  11.2K  11.2K  11.2K  11.2K  [FAIL]
Heap:     0      0.4K   0.4K   0.4K   0.9K   0.9K   1.8K   3.6K   7.2K
Hybrid:   1.8K   1.8K   1.8K   1.8K   3.6K   3.6K   3.6K   7.2K   14.4K
          ↑                             ↑
       Embedded                    Migration point (T = HEAP_THRESHOLD)

Legend: T = HEAP_THRESHOLD (default: 16)
```

### Operation Costs

| Operation | Stack | Heap (Pure) | Hybrid |
|-----------|-------|-------------|--------|
| Add (1-T) | O(1) | O(1) amortized | O(1) — stack |
| Add (T+1) | FAIL | O(1) amortized | O(n) — one-time migration, then O(1) |
| Access | O(1) | O(1) | O(1) — with flag check |
| Memory for 10 | 11.2 KB | ~1 KB | 1.8 KB (embedded) |
| Memory for 100 | FAIL | ~14 KB | ~14 KB |

Note: T = HEAP_THRESHOLD (configurable, default: 16)

## Code Structure Overview

```mermaid
classDiagram
    class t_world {
        +t_sphere stack_spheres[HEAP_THRESHOLD]
        +t_sphere* heap_spheres
        +int spheres_count
        +int heap_capacity
        +bool using_heap
    }
    
    class Operations {
        +world_make()
        +world_add_sphere()
        +world_get_sphere()
        +free_world()
    }
    
    class StackOps {
        -add_to_stack()
        -access_stack()
    }
    
    class HeapOps {
        -migrate_to_heap()
        -add_to_heap()
        -grow_heap()
        -access_heap()
    }
    
    t_world --> Operations
    Operations --> StackOps : count < HEAP_THRESHOLD
    Operations --> HeapOps : count >= HEAP_THRESHOLD
    StackOps --> HeapOps : migration
```

## Modular Code Organization

**For easy stack-only mode:** Isolate all heap logic in separate directory.

```
src/world/
├── world_common.c       # Shared code
├── world_stack.c        # Pure stack (STRATEGY_STACK)
└── heap/                # ← Delete this folder for pure stack!
    ├── world_hybrid.c   # Hybrid add/access
    ├── heap_migrate.c   # Migration logic
    └── heap_grow.c      # Realloc logic

include/
└── memory_config.h      # ⚙️ Set HEAP_THRESHOLD or disable heap
```

**To disable heap:**
1. Edit `memory_config.h`: `#define STRATEGY_STACK`
2. Delete `src/world/heap/` directory (optional)
3. Recompile → pure stack implementation!

## See Also
- [Hybrid Heap Transition Plan](hybrid-heap-transition.md) — Implementation roadmap with HEAP_THRESHOLD configuration
- [Architecture Comparison](architecture-comparison.md) — Detailed benchmark and decision guide
- [Full Heap Migration](heap-transition.md) — Alternative approach (pure heap)
- [Memory Management](memory-management.md) — Leak detection

---

*Hybrid architecture flowchart for miniRT. Combines stack speed with heap flexibility. Configure HEAP_THRESHOLD to tune behavior.*
