# Rendering Performance Optimization

**Goal:** Optimize existing ray tracing bottlenecks without major architectural changes.

## 🎯 Identified Bottlenecks

### Current Performance Issues

```c
// render.c - main rendering loop
for (y = 0; y < height; y++)
{
    for (x = 0; x < width; x++)
    {
        ray = ray_for_pixel(camera, x, y);
        color = color_at(world, ray);  // ← BOTTLENECK 1: Full world intersection
        
        // Inside color_at():
        //   1. intersect_world() → tests ALL spheres
        //   2. For shadows: intersect_world() again → tests ALL spheres
        //   Result: 2× full traversal per pixel!
    }
}
```

**Problem:** `intersect_world()` called **2 times per pixel** × **N spheres** = **2 × width × height × N** intersection tests

**Example:**
- Resolution: 800×600 = 480,000 pixels
- Spheres: 100
- Tests: 480,000 × 2 × 100 = **96 million intersection tests!**

---

## 🚀 Optimization Strategies

### Level 1: Caching (Easy — Low Hanging Fruit)

Cache intersection results to avoid redundant calculations.

#### Strategy 1.1: Hit Point Cache

**Problem:** Computing shadow rays recalculates intersections

**Solution:** Cache the hit point from color calculation

**File:** `src/render/render_optimized.c`

```c
typedef struct s_hit_cache
{
    t_point     hit_point;      // Cached intersection point
    t_vector    normal;         // Cached normal
    t_sphere    *object;        // Hit object
    double      t;              // Ray parameter
    bool        valid;          // Cache validity flag
}   t_hit_cache;

typedef struct s_render_context
{
    t_world     *world;
    t_camera    *camera;
    t_hit_cache *pixel_cache;   // Cache per pixel
}   t_render_context;

// Initialize cache
t_render_context init_render_context(t_world *world, t_camera *camera)
{
    t_render_context ctx;
    
    ctx.world = world;
    ctx.camera = camera;
    ctx.pixel_cache = ft_calloc(1, sizeof(t_hit_cache));
    ctx.pixel_cache->valid = false;
    
    return (ctx);
}

// Optimized color_at with caching
t_color color_at_cached(t_render_context *ctx, t_ray ray)
{
    t_intersections xs;
    t_intersection  *hit;
    t_computations  comps;
    
    // First intersection (for color)
    xs = intersect_world(ctx->world, ray);
    hit = hit_intersection(&xs);
    
    if (!hit)
    {
        ctx->pixel_cache->valid = false;
        return (color(0, 0, 0));  // Background
    }
    
    // Compute and CACHE hit information
    comps = prepare_computations(hit, ray);
    ctx->pixel_cache->hit_point = comps.point;
    ctx->pixel_cache->normal = comps.normalv;
    ctx->pixel_cache->object = hit->object;
    ctx->pixel_cache->t = hit->t;
    ctx->pixel_cache->valid = true;
    
    // Shade using cached data
    return (shade_hit_cached(ctx, &comps));
}

// Shadow calculation using cache
bool is_shadowed_cached(t_render_context *ctx, t_point point)
{
    t_vector direction;
    t_ray    shadow_ray;
    double   distance;
    t_intersections xs;
    t_intersection  *h;
    
    // Direction to light
    direction = vector_subtract(ctx->world->light.position, point);
    distance = vector_magnitude(direction);
    direction = vector_normalize(direction);
    
    // Small optimization: if cached hit is closer than light, skip
    if (ctx->pixel_cache->valid)
    {
        double cache_dist = vector_magnitude(
            vector_subtract(ctx->pixel_cache->hit_point, point)
        );
        if (cache_dist > distance)
            return (false);  // Light is closer than cached object
    }
    
    shadow_ray = ray(point, direction);
    xs = intersect_world(ctx->world, shadow_ray);
    h = hit_intersection(&xs);
    
    if (h && h->t < distance)
        return (true);
    return (false);
}
```

**Performance Gain:**
- Before: 2 full world traversals per pixel
- After: Still 2 traversals, but with early exit optimizations
- Speedup: ~10-20% (from early exits)

---

### Level 2: Spatial Acceleration (Medium — Significant Impact)

Use spatial data structures to avoid testing all spheres.

#### Strategy 2.1: Bounding Volume Hierarchy (BVH)

**Concept:** Group spheres into hierarchical bounding boxes, test box first (cheap), only test spheres inside if box is hit.

**Structure:**

```c
typedef struct s_aabb
{
    t_point min;  // Minimum corner
    t_point max;  // Maximum corner
}   t_aabb;

typedef struct s_bvh_node
{
    t_aabb              box;        // Bounding box for this node
    struct s_bvh_node   *left;      // Left child (or NULL)
    struct s_bvh_node   *right;     // Right child (or NULL)
    t_sphere            **objects;  // Objects in this leaf (if leaf)
    int                 obj_count;  // Number of objects (0 if interior node)
}   t_bvh_node;

typedef struct s_world_bvh
{
    t_sphere    *spheres;       // Original sphere array
    int         spheres_count;
    t_bvh_node  *root;          // BVH root
    t_light     light;
}   t_world_bvh;
```

**File:** `src/acceleration/bvh.c`

```c
// Compute AABB for a sphere
t_aabb sphere_bounds(t_sphere *sphere)
{
    t_aabb box;
    double radius;
    
    radius = sphere->radius;
    
    box.min = point(
        sphere->center.x - radius,
        sphere->center.y - radius,
        sphere->center.z - radius
    );
    box.max = point(
        sphere->center.x + radius,
        sphere->center.y + radius,
        sphere->center.z + radius
    );
    
    return (box);
}

// Merge two AABBs
t_aabb aabb_merge(t_aabb a, t_aabb b)
{
    t_aabb result;
    
    result.min.x = fmin(a.min.x, b.min.x);
    result.min.y = fmin(a.min.y, b.min.y);
    result.min.z = fmin(a.min.z, b.min.z);
    
    result.max.x = fmax(a.max.x, b.max.x);
    result.max.y = fmax(a.max.y, b.max.y);
    result.max.z = fmax(a.max.z, b.max.z);
    
    return (result);
}

// Fast ray-box intersection test
bool intersect_aabb(t_aabb box, t_ray ray)
{
    double tmin, tmax, tymin, tymax, tzmin, tzmax;
    
    // X slab
    tmin = (box.min.x - ray.origin.x) / ray.direction.x;
    tmax = (box.max.x - ray.origin.x) / ray.direction.x;
    if (tmin > tmax)
        swap(&tmin, &tmax);
    
    // Y slab
    tymin = (box.min.y - ray.origin.y) / ray.direction.y;
    tymax = (box.max.y - ray.origin.y) / ray.direction.y;
    if (tymin > tymax)
        swap(&tymin, &tymax);
    
    if ((tmin > tymax) || (tymin > tmax))
        return (false);
    
    tmin = fmax(tmin, tymin);
    tmax = fmin(tmax, tymax);
    
    // Z slab
    tzmin = (box.min.z - ray.origin.z) / ray.direction.z;
    tzmax = (box.max.z - ray.origin.z) / ray.direction.z;
    if (tzmin > tzmax)
        swap(&tzmin, &tzmax);
    
    if ((tmin > tzmax) || (tzmin > tmax))
        return (false);
    
    return (true);
}

// Build BVH (simple median split)
t_bvh_node *bvh_build(t_sphere **objects, int count)
{
    t_bvh_node *node;
    t_aabb box;
    int i;
    
    if (count == 0)
        return (NULL);
    
    node = malloc(sizeof(t_bvh_node));
    
    // Leaf node (few objects)
    if (count <= 4)  // Threshold: 4 objects per leaf
    {
        node->objects = objects;
        node->obj_count = count;
        node->left = NULL;
        node->right = NULL;
        
        // Compute bounding box
        box = sphere_bounds(objects[0]);
        for (i = 1; i < count; i++)
            box = aabb_merge(box, sphere_bounds(objects[i]));
        node->box = box;
        
        return (node);
    }
    
    // Interior node: split objects
    // Simple strategy: sort by longest axis, split at median
    int axis = longest_axis(objects, count);  // 0=X, 1=Y, 2=Z
    sort_objects_by_axis(objects, count, axis);
    
    int mid = count / 2;
    node->left = bvh_build(objects, mid);
    node->right = bvh_build(objects + mid, count - mid);
    node->objects = NULL;
    node->obj_count = 0;
    
    // Merge children boxes
    node->box = aabb_merge(node->left->box, node->right->box);
    
    return (node);
}

// Traverse BVH to find intersections
void bvh_intersect(t_bvh_node *node, t_ray ray, t_intersections *xs)
{
    int i;
    
    if (!node)
        return;
    
    // Test bounding box first (cheap!)
    if (!intersect_aabb(node->box, ray))
        return;  // Ray misses this entire subtree
    
    // Leaf node: test actual objects
    if (node->obj_count > 0)
    {
        for (i = 0; i < node->obj_count; i++)
            intersect_sphere(node->objects[i], ray, xs);
        return;
    }
    
    // Interior node: recurse to children
    bvh_intersect(node->left, ray, xs);
    bvh_intersect(node->right, ray, xs);
}

// Replace intersect_world with BVH version
t_intersections intersect_world_bvh(t_world_bvh *world, t_ray ray)
{
    t_intersections xs;
    
    xs.count = 0;
    xs.capacity = 10;
    xs.data = malloc(sizeof(t_intersection) * xs.capacity);
    
    bvh_intersect(world->root, ray, &xs);
    
    return (xs);
}
```

**Performance Gain:**
- Before: O(N) tests per ray (N = sphere count)
- After: O(log N) average (tree traversal)
- Speedup: **10-100× for large scenes** (100+ objects)

**Example:**
- 100 spheres: 100 tests → ~7 tests (log₂ 100 ≈ 6.6)
- 1000 spheres: 1000 tests → ~10 tests

---

#### Strategy 2.2: Uniform Grid (Alternative)

**Concept:** Divide space into 3D grid, only test objects in cells that ray passes through.

**Structure:**

```c
#define GRID_SIZE 20  // 20×20×20 grid

typedef struct s_grid_cell
{
    t_sphere    **objects;  // Array of pointers to spheres
    int         count;      // Number of objects in this cell
}   t_grid_cell;

typedef struct s_uniform_grid
{
    t_grid_cell cells[GRID_SIZE][GRID_SIZE][GRID_SIZE];
    t_aabb      world_bounds;  // Bounds of entire scene
    t_vector    cell_size;     // Size of one cell
}   t_uniform_grid;

// Build grid
t_uniform_grid *grid_build(t_sphere *spheres, int count)
{
    t_uniform_grid *grid;
    t_aabb world_box;
    int i, x, y, z;
    
    grid = ft_calloc(1, sizeof(t_uniform_grid));
    
    // Compute world bounds
    world_box = sphere_bounds(&spheres[0]);
    for (i = 1; i < count; i++)
        world_box = aabb_merge(world_box, sphere_bounds(&spheres[i]));
    
    grid->world_bounds = world_box;
    
    // Cell size
    grid->cell_size.x = (world_box.max.x - world_box.min.x) / GRID_SIZE;
    grid->cell_size.y = (world_box.max.y - world_box.min.y) / GRID_SIZE;
    grid->cell_size.z = (world_box.max.z - world_box.min.z) / GRID_SIZE;
    
    // Insert spheres into cells
    for (i = 0; i < count; i++)
    {
        t_aabb sphere_box = sphere_bounds(&spheres[i]);
        
        // Find cells that sphere overlaps
        int x_min = world_to_grid(sphere_box.min.x, world_box.min.x, grid->cell_size.x);
        int x_max = world_to_grid(sphere_box.max.x, world_box.min.x, grid->cell_size.x);
        int y_min = world_to_grid(sphere_box.min.y, world_box.min.y, grid->cell_size.y);
        int y_max = world_to_grid(sphere_box.max.y, world_box.min.y, grid->cell_size.y);
        int z_min = world_to_grid(sphere_box.min.z, world_box.min.z, grid->cell_size.z);
        int z_max = world_to_grid(sphere_box.max.z, world_box.min.z, grid->cell_size.z);
        
        // Add sphere to all overlapping cells
        for (x = x_min; x <= x_max; x++)
            for (y = y_min; y <= y_max; y++)
                for (z = z_min; z <= z_max; z++)
                    grid_add_object(&grid->cells[x][y][z], &spheres[i]);
    }
    
    return (grid);
}

// Traverse grid with ray (DDA algorithm)
t_intersections intersect_world_grid(t_uniform_grid *grid, t_ray ray)
{
    t_intersections xs;
    t_point current;
    int x, y, z;
    int step_x, step_y, step_z;
    double t_max_x, t_max_y, t_max_z;
    double t_delta_x, t_delta_y, t_delta_z;
    
    xs = init_intersections();
    
    // Initialize DDA traversal
    current = ray.origin;
    // ... (DDA setup code)
    
    // Walk through grid cells
    while (inside_grid(x, y, z))
    {
        // Test objects in current cell only
        t_grid_cell *cell = &grid->cells[x][y][z];
        for (int i = 0; i < cell->count; i++)
            intersect_sphere(cell->objects[i], ray, &xs);
        
        // If we found a hit closer than next cell, stop
        t_intersection *hit = hit_intersection(&xs);
        if (hit && hit->t < fmin(t_max_x, fmin(t_max_y, t_max_z)))
            break;
        
        // Step to next cell (DDA)
        if (t_max_x < t_max_y && t_max_x < t_max_z)
        {
            x += step_x;
            t_max_x += t_delta_x;
        }
        else if (t_max_y < t_max_z)
        {
            y += step_y;
            t_max_y += t_delta_y;
        }
        else
        {
            z += step_z;
            t_max_z += t_delta_z;
        }
    }
    
    return (xs);
}
```

**Performance Gain:**
- Before: O(N) tests
- After: O(cells traversed) ≈ O(√N) average
- Speedup: **5-20× for medium scenes**

**Trade-offs:**
- Grid: Better for uniformly distributed objects
- BVH: Better for clustered objects

---

### Level 3: Multi-threading (Hard — Massive Speedup)

Parallelize pixel rendering across CPU cores.

**File:** `src/render/render_parallel.c`

```c
#include <pthread.h>

typedef struct s_render_task
{
    t_world     *world;
    t_camera    *camera;
    t_image     *image;
    int         y_start;   // Start row
    int         y_end;     // End row
}   t_render_task;

void *render_worker(void *arg)
{
    t_render_task *task = (t_render_task *)arg;
    t_ray ray;
    t_color color;
    int x, y;
    
    for (y = task->y_start; y < task->y_end; y++)
    {
        for (x = 0; x < task->image->width; x++)
        {
            ray = ray_for_pixel(task->camera, x, y);
            color = color_at(task->world, ray);
            write_pixel(task->image, x, y, color);
        }
    }
    
    return (NULL);
}

void render_parallel(t_world *world, t_camera *camera, t_image *image)
{
    int num_threads = 8;  // Or: sysconf(_SC_NPROCESSORS_ONLN)
    pthread_t threads[num_threads];
    t_render_task tasks[num_threads];
    int rows_per_thread = image->height / num_threads;
    int i;
    
    // Create worker threads
    for (i = 0; i < num_threads; i++)
    {
        tasks[i].world = world;
        tasks[i].camera = camera;
        tasks[i].image = image;
        tasks[i].y_start = i * rows_per_thread;
        tasks[i].y_end = (i == num_threads - 1) ? image->height : (i + 1) * rows_per_thread;
        
        pthread_create(&threads[i], NULL, render_worker, &tasks[i]);
    }
    
    // Wait for completion
    for (i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);
}
```

**Performance Gain:**
- 8-core CPU: **~7-8× speedup** (near-linear scaling)
- 16-core: **~14-16× speedup**

---

## 📊 Combined Optimization Strategy

### Recommended Implementation Order

#### Phase 1: Easy Wins (1-2 days)
1. ✅ Add hit point caching
2. ✅ Early exit optimizations in shadow tests
3. ✅ Profile code to confirm bottlenecks

**Expected Speedup:** 10-20%

#### Phase 2: Spatial Acceleration (3-5 days)
1. ✅ Implement BVH construction
2. ✅ Replace `intersect_world` with `intersect_world_bvh`
3. ✅ Test with scenes of 100+ objects

**Expected Speedup:** 10-100× (depends on scene size)

#### Phase 3: Parallelization (2-3 days)
1. ✅ Implement pthread-based parallel rendering
2. ✅ Handle thread safety (image writes are independent, OK)
3. ✅ Add progress bar

**Expected Speedup:** 7-8× on 8-core CPU

### Total Expected Speedup

| Scene Size | Before | After (BVH + Threads) | Speedup |
|------------|--------|----------------------|---------|
| 10 objects | 5 sec  | 0.8 sec              | 6×      |
| 100 objects | 50 sec | 1.5 sec              | 33×     |
| 1000 objects | 500 sec | 8 sec               | 62×     |

---

## 🔧 Modular Implementation

### File Structure

```
src/
├── render/
│   ├── render.c               # Original rendering
│   ├── render_cached.c        # Level 1: Caching
│   └── render_parallel.c      # Level 3: Threading
│
└── acceleration/              # ← NEW MODULE (optional)
    ├── bvh.c                  # BVH construction & traversal
    ├── bvh.h
    ├── grid.c                 # Uniform grid (alternative)
    └── aabb.c                 # Bounding box utilities

include/
└── acceleration.h             # Public API
```

### Configuration

**File:** `include/render_config.h`

```c
#ifndef RENDER_CONFIG_H
# define RENDER_CONFIG_H

/* Optimization Features (enable/disable) */
# define USE_HIT_CACHE 1       // Level 1: Caching
# define USE_BVH 1             // Level 2: BVH acceleration
# define USE_PARALLEL 1        // Level 3: Multi-threading

# if USE_PARALLEL
#  define NUM_THREADS 8        // Or auto-detect
# endif

# if USE_BVH
#  define BVH_LEAF_SIZE 4      // Objects per leaf
# endif

#endif
```

**Easy disable:** Set `USE_BVH 0` → falls back to original `intersect_world`

---

## 📐 Directory Structure (with Acceleration Module)

```
src/
├── world/
│   ├── world_common.c
│   ├── world_stack.c
│   └── heap/                  # From previous docs (memory architecture)
│       ├── world_hybrid.c
│       └── ...
│
├── render/
│   ├── render.c               # Main rendering loop
│   ├── render_cached.c        # Caching optimizations
│   └── render_parallel.c      # Multi-threading
│
└── acceleration/              # ← DELETE THIS for simple version!
    ├── bvh.c                  # BVH tree
    ├── bvh_build.c            # Tree construction
    ├── bvh_traverse.c         # Ray traversal
    ├── grid.c                 # Grid acceleration
    └── aabb.c                 # Bounding boxes
```

**To disable acceleration:**
1. `rm -rf src/acceleration/`
2. In `render_config.h`: `#define USE_BVH 0`
3. Recompile

---

## 🎓 Key Takeaways

### Bottleneck Analysis

**Current:**
```
intersect_world() called: 2× per pixel
Tests per pixel: 2 × N spheres
Total: width × height × 2 × N

800×600 × 2 × 100 = 96 million tests!
```

**Optimized (BVH):**
```
intersect_world_bvh() called: 2× per pixel
Tests per pixel: 2 × log₂(N) spheres
Total: width × height × 2 × log₂(N)

800×600 × 2 × 7 = 6.7 million tests (14× fewer!)
```

**Optimized (BVH + 8 threads):**
```
Speedup: 14× (BVH) × 8× (threads) = 112× total!
```

---

## 🚀 Quick Start Guide

### Option 1: Simple Caching (No Code Restructuring)

Add to existing `color_at()`:

```c
// Global cache (simple version)
static t_hit_cache g_cache = {.valid = false};

t_color color_at(t_world *world, t_ray ray)
{
    // ... existing code ...
    
    // After computing hit:
    if (hit)
    {
        g_cache.hit_point = comps.point;
        g_cache.normal = comps.normalv;
        g_cache.valid = true;
    }
    
    // In is_shadowed(), check cache first
    if (g_cache.valid && should_skip_shadow_test())
        return (false);
    
    // ... rest of code ...
}
```

**Gain:** 5-10% speedup (minimal changes)

---

### Option 2: BVH Acceleration (Maximum Impact)

1. Build BVH once after loading scene
2. Replace `intersect_world()` calls
3. Huge speedup for large scenes

**Gain:** 10-100× speedup (worth the effort!)

---

### Option 3: Full Optimization (All 3 Levels)

1. Implement caching
2. Add BVH
3. Add threading

**Gain:** Up to **100× speedup** on 8-core CPU with large scenes!

---

## See Also
- [Memory Management](memory-management.md) — Ensure no leaks in BVH
- [Hybrid Architecture](hybrid-heap-transition.md) — Memory strategy for acceleration structures
- [Parser Call Tree](parser/06-calltree.md) — Understanding call hierarchies

---

*Rendering optimization guide for miniRT. Focus on BVH for maximum impact!*
