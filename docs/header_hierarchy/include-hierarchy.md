# Include Hierarchy — Geometry Modules

This diagram shows the `#include` dependencies for cylinders and spheres modules.

## Cylinders module

```
┌─────────────────────────────────┐
│  cylinders.h                    │
│  #include "shapes.h"            │
│  #include "intersect.h"         │
└─────────────────────────────────┘

┌─────────────────────────────────┐
│  cylinders.c                    │
│  #include "cylinders.h"         │
│  #include <math.h>              │
│  #include "defines.h"           │
└─────────────────────────────────┘

┌─────────────────────────────────┐
│  cylinder_intersect.c           │
│  #include "cylinders.h"         │
│  #include "math_utils.h"        │
└─────────────────────────────────┘

┌─────────────────────────────────┐
│  cylinder_normal.c              │
│  #include "cylinders.h"         │
│  #include "matrices.h"          │
└─────────────────────────────────┘
```

## Spheres module

```
┌─────────────────────────────────┐
│  spheres.h                      │
│  #include <stdbool.h>           │
│  #include <stddef.h>            │
│  #include "tuples.h"            │
│  #include "matrices.h"          │
│  #include "rays.h"              │
└─────────────────────────────────┘

┌─────────────────────────────────┐
│  spheres.c                      │
│  #include "spheres.h"           │
│  #include <stdlib.h>            │
│  #include <math.h>              │
│  #include <stdio.h>             │
└─────────────────────────────────┘

┌─────────────────────────────────┐
│  sphere_intersect.c             │
│  #include "spheres.h"           │
│  #include <math.h>              │
│  #include "intersect.h"         │
└─────────────────────────────────┘

┌─────────────────────────────────┐
│  sphere_normal.c                │
│  #include "spheres.h"           │
│  #include <math.h>              │
└─────────────────────────────────┘

┌─────────────────────────────────┐
│  sphere_render.c                │
│  #include "render_sphere.h"     │
│  #include "colors.h"            │
└─────────────────────────────────┘

┌─────────────────────────────────┐
│  sphere_render_grid.c           │
│  #include "render_sphere.h"     │
│  #include "intersect.h"         │
└─────────────────────────────────┘

┌─────────────────────────────────┐
│  sphere_render_phong.c          │
│  #include "render_sphere.h"     │
│  #include "intersect.h"         │
│  #include "colors.h"            │
│  #include "lighting.h"          │
└─────────────────────────────────┘
```

## Pattern

- All `.c` files include their module header first
- System headers: `<header.h>`
- Project headers: `"header.h"`
- **Cylinders**: 3 files, minimal dependencies
- **Spheres**: 6 files, includes rendering variants
