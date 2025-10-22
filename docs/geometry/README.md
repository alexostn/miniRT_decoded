# Geometry Module Documentation

This directory contains comprehensive documentation for the geometry system in miniRT: how geometric shapes (spheres, planes, cylinders, cones) are represented, transformed, and intersected by rays.

## Documentation Files

| File | Description |
|------|-------------|
| [01-components.md](01-components.md) | Component architecture — file structure, data types, dependencies |

## Quick Start

**New to the geometry system?** Start here:
1. Read [Component View](01-components.md) to understand the overall structure
2. Look at `include/shapes.h` for the base shape type
3. Examine `include/spheres.h` for a concrete example
4. Study `src/spheres/sphere_intersect.c` to see intersection math

## Key Concepts

### Shape Hierarchy

```
t_shape (base)
    ├─→ t_sphere
    ├─→ t_plane
    ├─→ t_cylinder
    └─→ t_cone
```

All shapes share:
- **Transform**: 4×4 matrix for position, rotation, scale
- **Material**: Color and lighting properties

### Transformation Flow

```
World Space → inverse(transform) → Object Space
                                       ↓
                                  intersection
                                       ↓
                                  local normal
                                       ↓
           transpose(inverse(transform))
                                       ↓
                                  World Normal
```

### Intersection Types

- **Sphere**: Quadratic equation `at² + bt + c = 0`
- **Plane**: Linear equation `t = -origin.y / direction.y`
- **Cylinder**: Quadratic in cylindrical coordinates
- **Cone**: Quadratic with cone parameters

## File Structure

```
src/
├── shapes/shapes.c              ← Base shape operations
├── spheres/                     ← Sphere implementation
│   ├── spheres.c
│   ├── sphere_intersect.c
│   ├── sphere_normal.c
│   └── sphere_render*.c
├── planes/planes.c              ← Plane implementation
├── cylinders/cylinders.c        ← Cylinder implementation
├── cones/cones.c                ← Cone implementation
└── intersections/               ← Intersection management
    ├── intersections.c
    └── utils.c

include/
├── shapes.h                     ← Base definitions
├── spheres.h                    ← Sphere types
├── planes.h                     ← Plane types
├── cylinders.h                  ← Cylinder types
├── cones.h                      ← Cone types
└── intersect.h                  ← Intersection types
```

## Core Functions by Shape

### Sphere
- `sphere_create()` — Create unit sphere at origin
- `sphere_intersect(s, r)` — Ray-sphere intersection
- `sphere_normal_at(s, p)` — Normal vector at point
- `sphere_set_transform(s, t)` — Apply transformation

### Plane
- `plane_create()` — Create XZ plane at y=0
- `plane_intersect(p, r)` — Ray-plane intersection
- `plane_local_normal_at(p)` — Always (0,1,0) in local space

### Cylinder
- `cylinder_create()` — Create infinite cylinder along Y axis
- `cylinder_intersect(c, r)` — Ray-cylinder intersection
- `cylinder_normal_at(c, p)` — Normal perpendicular to axis

### Cone
- `cone_create()` — Create double-napped cone
- `cone_intersect(c, r)` — Ray-cone intersection
- `cone_normal_at(c, p)` — Normal based on cone angle

## Common Patterns

### Creating and Positioning a Shape

```c
// Create shape
t_sphere s = sphere_create();

// Set material
t_material m = material();
m.color = color(1, 0, 0);  // red
m.diffuse = 0.7;
s = sphere_set_material(s, m);

// Position and scale
t_matrix transform = mat_mul(
    translation(0, 1, 0),      // move up
    scaling(2, 2, 2)           // double size
);
s = sphere_set_transform(s, transform);
```

### Checking Intersection

```c
// Create ray
t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));

// Find intersections
t_xs xs = sphere_intersect(&sphere, r);

// Get closest hit
t_intersection *hit = hit(&xs);
if (hit) {
    // Ray hit the sphere at distance hit->t
    t_tuple hit_point = ray_position(r, hit->t);
    t_tuple normal = sphere_normal_at(sphere, hit_point);
}
```

### Computing Normal

```c
// Get normal at world point
t_tuple world_point = point(1, 0, 0);
t_tuple normal = sphere_normal_at(&sphere, world_point);

// Normal is automatically:
// 1. Transformed to object space
// 2. Computed in local coordinates
// 3. Transformed back to world space
// 4. Normalized
```

## Math Reference

### Sphere Intersection

Given ray `r(t) = o + td` and sphere at center `c` with radius `r`:

```
|r(t) - c|² = r²

Expanding:
a = d · d
b = 2 × d · (o - c)
c = (o - c) · (o - c) - r²

Discriminant: Δ = b² - 4ac
If Δ < 0: no intersection
If Δ ≥ 0: t = (-b ± √Δ) / 2a
```

### Plane Intersection

Given ray `r(t) = o + td` and plane with normal `n` at point `p`:

```
(r(t) - p) · n = 0
(o + td - p) · n = 0
t × (d · n) = (p - o) · n
t = (p - o) · n / (d · n)

If |d · n| < ε: ray parallel to plane (no intersection)
```

### Normal Transformation

To transform normal from object to world space:

```
object_normal = local_normal_at(object_point)
world_normal = transpose(inverse(transform)) × object_normal
world_normal.w = 0  // ensure it's a vector
return normalize(world_normal)
```

## Related Documentation

- [Matrix Operations](../matrices/) — Transformations and linear algebra
- [Parser Documentation](../parser/) — How objects are loaded from .rt files
- [Rendering Pipeline](../rendering/) — How geometry integrates with rendering
- [Lighting & Materials](../lighting/) — Surface appearance and shading

## Implementation Notes

### Memory Management
- Shapes use **stack allocation** (they're value types)
- No dynamic memory for individual shapes
- World array stores shapes by value

### Coordinate Systems
- **World Space**: Scene coordinates
- **Object/Local Space**: Canonical shape position (e.g., unit sphere at origin)
- **Camera Space**: Relative to camera (used in rendering)

### Intersection Algorithm Choice
- **Analytical solutions** (quadratic/linear equations) for simple shapes
- Precise and fast
- Alternative: numerical methods for complex shapes (not used in miniRT)

### Performance
- Pre-compute inverse transforms where possible
- Early ray rejection using bounding volumes (not implemented in base miniRT)
- Intersection tests are the main bottleneck in ray tracing

## Debugging Tips

### Ray-Object Intersection Issues
1. Check transformation matrices (print or visualize)
2. Verify ray is transformed to object space correctly
3. Check discriminant calculation in quadratic solver
4. Ensure t values are positive (intersections ahead of ray origin)

### Normal Calculation Issues
1. Verify point is on surface (substitute into equation)
2. Check normal transformation (should use transpose of inverse)
3. Ensure normal is normalized (length = 1)
4. Check normal direction (should point away from surface)

### Visualization
```c
// Print ray
printf("Ray: origin(%.2f, %.2f, %.2f) dir(%.2f, %.2f, %.2f)\n",
    r.origin.x, r.origin.y, r.origin.z,
    r.direction.x, r.direction.y, r.direction.z);

// Print intersection
if (xs.count > 0) {
    printf("Intersections: %d\n", xs.count);
    for (int i = 0; i < xs.count; i++)
        printf("  t[%d] = %.2f\n", i, xs.intersections[i].t);
}
```

## Future Extensions

Possible additions to geometry system:
- **Bounding boxes** for optimization
- **Triangle meshes** for complex models
- **CSG operations** (union, intersection, difference)
- **Quadric surfaces** (ellipsoids, paraboloids)
- **Implicit surfaces** (blob, metaballs)

---

*Geometry module documentation for miniRT. Last updated: October 2025.*
