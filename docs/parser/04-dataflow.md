# Parser Architecture — Data Flow View

This diagram shows how data flows and transforms through the parser pipeline.

## Color data flow (RGB example)

```
┌─────────────────────────────────────────────────────┐
│  .rt file (subject format)                          │
│  A 0.2 255,128,0                                    │
│        └──┬──┘                                      │
│           RGB (0-255)                               │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Parser (parse_color_rgb)                           │
│  • Reads: "255,128,0"                               │
│  • Validates: RGB values in [0-255] range           │
│    (rejects >255 with error, not clamping)          │
│  • Converts: rgb_to_normalized(255) = 1.0           │
│  • Returns: color(1.0, 0.5, 0.0)  ← t_tuple         │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Scene storage (t_scene)                            │
│  scene->ambient_color = (1.0, 0.5, 0.0, 0.0)        │
│                          └────┬────┘                │
│                          0-1 range (float)          │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Rendering (ray tracing)                            │
│  • Lighting calculations in 0-1 range               │
│  • Phong shading, shadows, etc.                     │
│  • final_color = ambient + diffuse + specular       │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  MLX conversion (color_to_mlx)                      │
│  • Input: t_tuple (0-1)                             │
│  • clamp_channel(1.0) = 255                         │
│  • clamp_channel(0.5) = 128                         │
│  • Output: 0xFFFF8000 (ARGB)                        │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  MLX display                                        │
│  image_put_pixel(canvas, x, y, 0xFFFF8000)          │
└─────────────────────────────────────────────────────┘
```

## Sphere data flow

```
┌─────────────────────────────────────────────────────┐
│  .rt file                                           │
│  sp 0,0,20 12.6 255,0,0                             │
│     └──┬─┘ └┬┘ └──┬──┘                              │
│     center  │   color                               │
│          diameter                                   │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Parser (parse_sphere)                              │
│  • center = parse_vector3("0,0,20")                 │
│    → point(0.0, 0.0, 20.0)                          │
│  • diameter = parse_double("12.6") → 12.6           │
│  • color = parse_color_rgb("255,0,0")               │
│    → color(1.0, 0.0, 0.0)                           │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Sphere creation (sphere_create)                    │
│  • Default sphere at origin, radius 1.0             │
│  • material.color = (1.0, 0.0, 0.0)                 │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Transformation (apply_sphere_transform)            │
│  • radius = diameter / 2 = 6.3                      │
│  • scale = scaling(6.3, 6.3, 6.3)                   │
│  • translate = translation(0, 0, 20)                │
│  • transform = translate × scale                    │
│  • sphere.transform = 4×4 matrix                    │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  World storage (world_add_sphere)                   │
│  • world.spheres[count] = sphere                    │
│  • world.spheres_count++                            │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Ray tracing                                        │
│  • Ray-sphere intersection (inverse transform)      │
│  • Normal calculation                               │
│  • Lighting with material.color                     │
└─────────────────────────────────────────────────────┘
```

## Camera data flow

```
┌─────────────────────────────────────────────────────┐
│  .rt file                                           │
│  C 0,0,-5 0,0,1 70                                  │
│    └──┬─┘ └─┬┘ └┬┘                                  │
│    position │  FOV                                  │
│          orientation                                │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Parser (parse_camera)                              │
│  • position = parse_vector3("0,0,-5")               │
│    → point(0.0, 0.0, -5.0)                          │
│  • orientation = parse_vector3("0,0,1")             │
│    → normalize → vector(0.0, 0.0, 1.0)              │
│  • fov_degrees = parse_double("70") → 70.0          │
│  • fov_radians = 70 × π/180 ≈ 1.22                  │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Scene storage (t_scene)                            │
│  • scene.camera.position = (0, 0, -5)               │
│  • scene.camera.orientation = (0, 0, 1)             │
│  • scene.camera.field_of_view = 1.22 rad            │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Camera setup (camera_make / view_transform)        │
│  • from = position                                  │
│  • to = position + orientation                      │
│  • up = vector(0, 1, 0) (or computed)               │
│  • transform = view_transform(from, to, up)         │
│  • aspect_ratio = width / height                    │
│  • half_view = tan(fov / 2)                         │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Rendering (ray_for_pixel)                          │
│  • For each pixel (x, y):                           │
│    - Calculate world coordinates                    │
│    - Apply inverse camera transform                 │
│    - Generate ray from camera through pixel         │
│    - Trace and return color                         │
└─────────────────────────────────────────────────────┘
```

## Light data flow

```
┌─────────────────────────────────────────────────────┐
│  .rt file                                           │
│  L -10,10,-10 0.7 255,255,255                       │
│    └────┬───┘ └┬┘ └────┬────┘                       │
│     position   │     color                          │
│            intensity                                │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Parser (parse_light)                               │
│  • position = parse_vector3("-10,10,-10")           │
│    → point(-10.0, 10.0, -10.0)                      │
│  • intensity = parse_double("0.7") → 0.7            │
│  • color = parse_color_rgb("255,255,255")           │
│    → color(1.0, 1.0, 1.0)                           │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Scene storage (t_scene)                            │
│  • world.light.position = (-10, 10, -10)            │
│  • world.light.intensity = 0.7                      │
│  • world.light.color = (1.0, 1.0, 1.0)              │
└───────────┬─────────────────────────────────────────┘
            ↓
┌───────────┴─────────────────────────────────────────┐
│  Lighting calculations (lighting function)          │
│  • Ambient: material.ambient × ambient_color        │
│  • Diffuse: light_dot_normal × light.intensity      │
│  • Specular: reflect_dot_eye^shininess × intensity  │
│  • Final: ambient + (diffuse + specular) × 0.7      │
└─────────────────────────────────────────────────────┘
```

## What this shows

**Data Flow Diagrams (DFD)** focus on how data moves and transforms:
- **Input formats**: strings from .rt file (RGB 0-255, coords, scalars)
- **Parsing stage**: string → normalized floats/vectors (t_tuple)
- **Storage**: scene/world structures with 0-1 colors, radians, transforms
- **Usage**: rendering with proper units (0-1 for colors, radians for angles)
- **Output**: MLX pixel format (ARGB hex)

This helps debug:
- Format mismatches (255 vs 1.0)
- Unit errors (degrees vs radians)
- Coordinate system issues (world vs camera space)
- Color clamping/overflow

Tip: compare with README.md (control flow) and README.sequence.md (interactions) for complete picture.
