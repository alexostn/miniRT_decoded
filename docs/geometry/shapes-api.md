# Shapes API Documentation

## Overview

All geometric objects in miniRT follow a unified creation pattern:

```
┌─────────────────────────────────────────────────────────────┐
│                    SHAPE CREATION PATTERN                   │
└─────────────────────────────────────────────────────────────┘
                              │
                              ▼
                   ┌──────────────────────┐
                   │  1. Create Default   │
                   │  Unit Shape at       │
                   │  Origin (0,0,0)      │
                   └──────────┬───────────┘
                              │
                              ▼
                   ┌──────────────────────┐
                   │  2. Apply Transform  │
                   │  - Translation       │
                   │  - Scaling           │
                   │  - Rotation          │
                   └──────────┬───────────┘
                              │
                              ▼
                   ┌──────────────────────┐
                   │  3. Set Material     │
                   │  - Color             │
                   │  - Lighting Props    │
                   └──────────────────────┘
```

This approach provides an elegant and flexible architecture where all objects are created as unit primitives at origin, then transformed to their final position.

---

## Shape Creation API

### Spheres

```c
t_sphere sphere_create(void);
t_sphere sphere_set_transform(t_sphere s, t_matrix transform);
t_sphere sphere_set_material(t_sphere s, t_material material);
```

**Usage Example:**
```c
t_sphere sphere = sphere_create();
sphere = sphere_set_transform(sphere, 
    mat_mul(translation(x, y, z), scaling(radius, radius, radius)));
sphere = sphere_set_material(sphere, material);
```

**Flow:**
```
sphere_create()
    │
    └──> Unit sphere at (0,0,0), radius=1
         │
         └──> sphere_set_transform(sphere, transforms)
              │
              └──> Scaled, moved, rotated sphere
                   │
                   └──> sphere_set_material(sphere, material)
                        │
                        └──> Final sphere ready for rendering
```

---

### Planes

```c
t_plane plane_create(void);
t_plane plane_set_transform(t_plane p, t_matrix transform);
t_plane plane_set_material(t_plane p, t_material material);
```

**Usage Example:**
```c
t_plane plane = plane_create();
plane = plane_set_transform(plane, translation(x, y, z));
plane = plane_set_material(plane, material);
```

**Flow:**
```
plane_create()
    │
    └──> XZ plane at y=0 (horizontal)
         │
         └──> plane_set_transform(plane, translation)
              │
              └──> Positioned plane
                   │
                   └──> plane_set_material(plane, material)
                        │
                        └──> Final plane ready for rendering
```

---

### Cylinders

```c
t_cylinder cylinder_create(void);
t_cylinder cylinder_set_transform(t_cylinder c, t_matrix transform);
t_cylinder cylinder_set_material(t_cylinder c, t_material material);
```

**Usage Example:**
```c
t_cylinder cylinder = cylinder_create();
cylinder = cylinder_set_transform(cylinder, 
    mat_mul(translation(x, y, z), scaling(radius, height/2, radius)));
cylinder = cylinder_set_material(cylinder, material);
```

**Flow:**
```
cylinder_create()
    │
    └──> Unit cylinder along Y-axis, radius=1
         │
         └──> cylinder_set_transform(cylinder, transforms)
              │
              └──> Scaled, moved, rotated cylinder
                   │
                   └──> cylinder_set_material(cylinder, material)
                        │
                        └──> Final cylinder ready for rendering
```

---

## Architecture Benefits

```
┌─────────────────────────────────────────────────────────────┐
│              TRANSFORMATION-BASED ARCHITECTURE              │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ✓ Uniformity     → All objects created identically        │
│  ✓ Flexibility    → Easy to combine transformations        │
│  ✓ Elegance       → Matches ray tracing math model         │
│  ✓ Extensibility  → Simple to add new object types         │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

## Internal Structure

All objects use the base `t_shape` structure:

```c
typedef struct s_shape
{
    t_matrix    transform;   // Transformation matrix
    t_material  material;    // Material properties
}   t_shape;
```

**Object Hierarchy:**
```
           ┌──────────┐
           │ t_shape  │
           │          │
           │ +transform
           │ +material│
           └────┬─────┘
                │
      ┌─────────┼─────────┐
      │         │         │
      ▼         ▼         ▼
 ┌─────────┐ ┌─────────┐ ┌─────────┐
 │t_sphere │ │t_plane  │ │t_cylinder│
 │         │ │         │ │         │
 │ +shape  │ │ +shape  │ │ +shape  │
 └─────────┘ └─────────┘ │ +min    │
                         │ +max    │
                         │ +closed │
                         └─────────┘
```

Concrete objects (`t_plane`, `t_cylinder`) contain `t_shape` internally and delegate transformation and material operations to the base `shape`.
