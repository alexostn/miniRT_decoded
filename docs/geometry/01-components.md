# Scene Geometry — Component View

This diagram shows the architecture of geometric objects (shapes) in miniRT: spheres, planes, cylinders, and cones.

## Component Diagram

```
┌─────────────────────────────────────────────────────────────────────┐
│                          GEOMETRY MODULE                            │
└─────────────────────────────────────────────────────────────────────┘

┌──────────────────┐
│   shapes.h       │  ← Base shape structure
├──────────────────┤
│ t_shape          │
│ - transform      │  (4×4 matrix)
│ - material       │  (color, ambient, diffuse, specular, shininess)
└────────┬─────────┘
         │
         │ Inherited by all concrete shapes
         │
    ┌────┴─────┬────────────┬────────────┬────────────┐
    │          │            │            │            │
    ▼          ▼            ▼            ▼            ▼
┌─────────┐ ┌────────┐ ┌──────────┐ ┌────────┐ ┌─────────────┐
│spheres.h│ │planes.h│ │cylinders.h│ │cones.h│ │intersect.h  │
└─────────┘ └────────┘ └──────────┘ └────────┘ └─────────────┘
    │           │            │           │            │
    │           │            │           │            │
    ▼           ▼            ▼           ▼            ▼
┌─────────┐ ┌────────┐ ┌──────────┐ ┌────────┐ ┌─────────────┐
│ SPHERES │ │ PLANES │ │CYLINDERS │ │ CONES  │ │INTERSECTIONS│
└─────────┘ └────────┘ └──────────┘ └────────┘ └─────────────┘
```

## File Organization

```
src/
├── shapes/
│   └── shapes.c               ← Base shape operations
│
├── spheres/
│   ├── spheres.c              ← Sphere creation
│   ├── sphere_intersect.c     ← Ray-sphere intersection
│   ├── sphere_normal.c        ← Normal calculation
│   ├── sphere_render.c        ← Rendering utilities
│   ├── sphere_render_grid.c   ← Grid rendering
│   └── sphere_render_phong.c  ← Phong shading
│
├── planes/
│   └── planes.c               ← Plane operations
│
├── cylinders/
│   └── cylinders.c            ← Cylinder operations
│
├── cones/
│   └── cones.c                ← Cone operations
│
└── intersections/
    ├── intersections.c        ← Intersection management
    └── utils.c                ← Utility functions

include/
├── shapes.h                   ← Base shape definitions
├── spheres.h                  ← Sphere types & functions
├── planes.h                   ← Plane types & functions
├── cylinders.h                ← Cylinder types & functions
├── cones.h                    ← Cone types & functions
└── intersect.h                ← Intersection types & functions
```

## Data Structures

### Base Shape (shapes.h)

```c
typedef struct s_shape
{
    t_matrix    transform;    // Transformation matrix (position, rotation, scale)
    t_material  material;     // Surface properties (color, lighting)
} t_shape;
```

**Purpose**: Common properties for all geometric objects

### Sphere (spheres.h)

```c
typedef struct s_sphere
{
    t_matrix    transform;    // Transformation (identity = unit sphere at origin)
    t_material  material;     // Surface appearance
} t_sphere;
```

**Default**: Unit sphere centered at origin (0,0,0) with radius 1
**Transform**: Scale for radius, translate for position

### Plane (planes.h)

```c
typedef struct s_plane
{
    t_shape shape;           // Contains transform + material
} t_plane;
```

**Default**: XZ plane at y=0
**Transform**: Rotation and translation to position plane

### Cylinder & Cone (cylinders.h, cones.h)

Similar structure to plane, containing `t_shape`

### Intersection (intersect.h)

```c
typedef struct s_intersection
{
    double  t;              // Distance along ray
    void    *object;        // Pointer to intersected object
} t_intersection;

typedef struct s_intersections
{
    int             count;
    int             capacity;
    t_intersection  intersections[MAX_INTERSECTIONS];
} t_xs;
```

## Component Responsibilities

### 1. Base Shape Module (shapes.c)

**File**: `src/shapes/shapes.c`

**Functions**:
- `shape_create()` — Initialize default shape
- `shape_set_transform(s, m)` — Apply transformation matrix
- `shape_set_material(s, mat)` — Set material properties
- `shape_transform_ray_to_local(s, r)` — Transform ray to object space
- `shape_normal_at(s, world_point, local_normal_fn)` — Calculate world-space normal

**Purpose**: Provides common operations shared by all shapes

### 2. Sphere Module (spheres/)

**Files**: 
- `spheres.c` — Creation and setup
- `sphere_intersect.c` — Intersection calculation
- `sphere_normal.c` — Normal vector calculation
- `sphere_render*.c` — Rendering utilities

**Core Functions**:
- `sphere_create()` — Create unit sphere at origin
- `sphere_set_transform(s, t)` — Position and scale sphere
- `sphere_set_material(s, m)` — Set appearance
- `sphere_intersect(s, r)` — Find ray-sphere intersections
- `sphere_normal_at(s, p)` — Calculate normal at point
- `transform_point_to_object_space(s, p)` — World → Object space

**Math**: 
- Intersection: Solve quadratic `at² + bt + c = 0`
- Normal: `normalize(object_point - center)`

### 3. Plane Module (planes/)

**File**: `src/planes/planes.c`

**Core Functions**:
- `plane_create()` — Create XZ plane
- `plane_local_normal_at(p)` — Normal is always (0,1,0) in local space
- `plane_local_intersect(p, ray)` — Check if ray hits plane
- `plane_intersect(p, r)` — World-space intersection

**Math**:
- Intersection: `t = -ray.origin.y / ray.direction.y` (if not parallel)
- Normal: Always `vector(0, 1, 0)` in local space

### 4. Cylinder Module (cylinders/)

**File**: `src/cylinders/cylinders.c`

**Operations**:
- Creation, transformation, material setup
- Intersection with infinite cylinder
- Normal calculation at surface

**Math**:
- Intersection: Quadratic equation in cylindrical coordinates
- Normal: Perpendicular to axis at intersection point

### 5. Cone Module (cones/)

**File**: `src/cones/cones.c`

**Operations**:
- Creation, transformation, material setup
- Intersection with double-napped cone
- Normal calculation

**Math**:
- Intersection: Quadratic equation with cone parameters
- Normal: Based on cone angle and intersection point

### 6. Intersection Module (intersections/)

**Files**: `intersections.c`, `utils.c`

**Core Functions**:
- `intersection(t, object)` — Create single intersection
- `intersections_create()` — Initialize collection
- `intersections_add(xs, i)` — Add intersection to collection
- `hit(xs)` — Find closest positive intersection
- `intersections_sort(xs)` — Sort by distance

**Purpose**: Manage multiple intersections, find visible hit

## Dependency Graph

```
shapes (base)
    ↓
    ├──→ spheres
    ├──→ planes
    ├──→ cylinders
    └──→ cones
         ↓
    intersections (uses all shapes)
         ↓
    rendering pipeline
```

## Intersection Calculation Flow

```
1. Ray Creation
   └─→ camera_ray_for_pixel(camera, x, y)

2. Transform Ray to Object Space
   └─→ shape_transform_ray_to_local(shape, ray)
       └─→ ray_transform(ray, inverse(shape.transform))

3. Local Intersection Calculation
   ├─→ sphere: solve at² + bt + c = 0
   ├─→ plane: check t = -origin.y / direction.y
   ├─→ cylinder: cylindrical coordinate equation
   └─→ cone: cone equation in local space

4. Collect Intersections
   └─→ intersections_add(xs, intersection(t, object))

5. Find Closest Hit
   └─→ hit(xs) returns intersection with smallest positive t

6. Calculate Normal at Hit Point
   └─→ Transform to object space → compute local normal → transform back
```

## Normal Calculation Flow

```
1. World Point Input
   └─→ e.g., sphere_normal_at(sphere, world_point)

2. Transform to Object Space
   └─→ object_point = inverse(transform) × world_point

3. Calculate Local Normal
   ├─→ sphere: normalize(object_point - origin)
   ├─→ plane: vector(0, 1, 0)
   ├─→ cylinder: perpendicular to axis
   └─→ cone: based on cone angle

4. Transform Normal to World Space
   └─→ world_normal = transpose(inverse(transform)) × local_normal
   └─→ normalize(world_normal)
```

## Example: Sphere Intersection

### Input
```
Ray: origin(0, 0, -5), direction(0, 0, 1)
Sphere: center(0, 0, 0), radius 1 (via scaling)
```

### Process
```
1. Transform ray to object space (if sphere has transform)
2. Calculate discriminant: Δ = b² - 4ac
3. If Δ < 0: no intersection
4. If Δ ≥ 0: calculate t₁ and t₂
   t₁ = (-b - √Δ) / 2a
   t₂ = (-b + √Δ) / 2a
5. Create intersections for both t values
6. Return t_xs with count=2
```

### Code Path
```c
sphere_intersect(sphere, ray)
  └─→ transform ray to object space
  └─→ calculate a, b, c coefficients
  └─→ discriminant = b² - 4ac
  └─→ if discriminant < 0: return empty xs
  └─→ t1 = (-b - sqrt(discriminant)) / (2 * a)
  └─→ t2 = (-b + sqrt(discriminant)) / (2 * a)
  └─→ add intersections to xs
  └─→ return xs
```

## Material Properties

All shapes have material that affects appearance:

```c
typedef struct s_material
{
    t_tuple color;      // RGB color (0-1 range)
    double  ambient;    // Ambient reflection (0-1)
    double  diffuse;    // Diffuse reflection (0-1)
    double  specular;   // Specular reflection (0-1)
    double  shininess;  // Specular exponent (10-200)
} t_material;
```

**Used in**: Phong shading calculation for final pixel color

## Transformation Pipeline

```
World Space
    ↓ inverse(shape.transform)
Object/Local Space
    ↓ intersection calculation
Hit Point (object space)
    ↓ normal calculation
Local Normal
    ↓ transpose(inverse(transform))
World Normal
    ↓ lighting calculation
Final Color
```

## Key Algorithms

### 1. Ray-Sphere Intersection (Quadratic)

```
Given: ray(t) = origin + t × direction
       sphere at center with radius r

Equation: |ray(t) - center|² = r²

Expanding:
a = direction · direction
b = 2 × direction · (origin - center)
c = (origin - center) · (origin - center) - r²

Discriminant: Δ = b² - 4ac
Solutions: t = (-b ± √Δ) / 2a
```

### 2. Ray-Plane Intersection (Linear)

```
Given: ray(t) = origin + t × direction
       plane with normal n at point p

Equation: (ray(t) - p) · n = 0

Solution: t = (p - origin) · n / (direction · n)

Note: If direction · n ≈ 0, ray is parallel (no intersection)
```

### 3. Normal at Point (Transformation)

```
1. object_point = inverse(transform) × world_point
2. local_normal = compute_local_normal(object_point)
3. world_normal = transpose(inverse(transform)) × local_normal
4. world_normal.w = 0  // ensure it's a vector
5. return normalize(world_normal)
```

## Adding New Shape Type

To add a new shape (e.g., torus):

1. **Create header** `include/torus.h`:
   ```c
   typedef struct s_torus {
       t_shape shape;
       double major_radius;
       double minor_radius;
   } t_torus;
   ```

2. **Create source** `src/torus/torus.c`:
   - `torus_create()`
   - `torus_local_intersect()`
   - `torus_local_normal_at()`

3. **Implement intersection math**:
   - Quartic equation for ray-torus intersection
   - Return t_xs with all valid t values

4. **Implement normal calculation**:
   - Use torus-specific geometry
   - Return normalized vector

5. **Add to world** via `world_add_torus()` or similar

## Testing Structure

```
tests/
├── test_shapes.c           ← Base shape tests
├── test_spheres.c          ← Sphere-specific tests
├── test_planes.c           ← Plane-specific tests
├── test_cylinders.c        ← Cylinder-specific tests
├── test_cones.c            ← Cone-specific tests
└── test_intersections.c    ← Intersection logic tests
```

## Performance Considerations

**Intersection Complexity**:
- Sphere: O(1) — quadratic equation
- Plane: O(1) — linear equation
- Cylinder: O(1) — quadratic equation
- Cone: O(1) — quadratic equation

**Bottlenecks**:
- Matrix inversion in `transform_ray_to_local()`
- Multiple intersections per ray (shadows, reflections)

**Optimization**: Pre-compute inverse transforms

## See Also

- [Transformation Matrices](../matrices/) — Positioning and scaling objects
- [Ray Tracing Pipeline](../rendering/) — How rays are traced through scene
- [Lighting & Shading](../lighting/) — How materials affect appearance
- [Parser](../parser/) — How scene objects are loaded from .rt files

---

*Component diagram for miniRT geometry system. Shows structure of spheres, planes, cylinders, cones, and intersection calculations.*
