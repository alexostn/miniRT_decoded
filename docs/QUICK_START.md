# Quick Start: Choosing Memory Architecture

## 🎯 TL;DR - Just tell me what to use!

**For miniRT (42 school):** Use **Hybrid** with `HEAP_THRESHOLD = 16` ✅

**Why?** 80% of test scenes benefit from zero malloc overhead.

---

## ⚙️ How to Configure

### Option 1: Hybrid (Recommended)

**File:** `include/memory_config.h`
```c
#define STRATEGY_HYBRID
#define HEAP_THRESHOLD 16  // Tune this: 8, 16, or 32
```

**Behavior:**
- 0-16 objects: stack (instant, no malloc)
- 17+ objects: migrates to heap (unlimited)

---

### Option 2: Pure Stack (Simple)

**File:** `include/memory_config.h`
```c
#define STRATEGY_STACK
#define MAX_OBJECTS 100
```

**Behavior:**
- Fixed limit: 100 objects
- No heap, no malloc/free
- Simplest code

**Downside:** Fails if scene > 100 objects

---

### Option 3: Pure Heap (Scalable)

**File:** `include/memory_config.h`
```c
#define STRATEGY_HEAP
#define HEAP_INITIAL_CAPACITY 4
#define HEAP_GROWTH_FACTOR 2
```

**Behavior:**
- Dynamic from start
- Unlimited objects
- More malloc overhead for small scenes

---

## 📊 Decision Tree

```
Do you have mostly small scenes (<20 objects)?
├─ YES → Hybrid (HEAP_THRESHOLD=16) ✅
└─ NO
   ├─ Are scenes huge (>100 objects)?
   │  └─ YES → Pure Heap
   └─ Do you want simplest code?
      ├─ YES → Pure Stack (if limit OK)
      └─ NO → Hybrid (safest choice)
```

---

## 📚 Full Documentation

1. **[Architecture Comparison](architecture-comparison.md)** — Read first! Detailed benchmarks
2. **[Hybrid Heap Transition](hybrid-heap-transition.md)** — Implementation guide
3. **[Hybrid Architecture Flowchart](hybrid-architecture-flowchart.md)** — Visual diagrams
4. **[Full Heap Migration](heap-transition.md)** — Pure heap approach

---

## 🔧 Quick Tuning Guide

**Problem:** Most scenes have 5-10 objects, wasting memory

**Solution:** Lower threshold
```c
#define HEAP_THRESHOLD 8  // Instead of 16
```

**Problem:** Getting migrations too often (scenes ~20 objects)

**Solution:** Raise threshold
```c
#define HEAP_THRESHOLD 32  // More stack usage
```

**Problem:** Hybrid is too complex, just want simple code

**Solution:** Switch to pure stack
```c
#define STRATEGY_STACK
#define MAX_OBJECTS 100
// Delete src/world/heap/ directory
```

---

*Quick start guide. For detailed analysis, see [architecture-comparison.md](architecture-comparison.md).*
