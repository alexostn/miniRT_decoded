# Parser Architecture — Call Tree View

This diagram shows the hierarchy of function calls in the parser, from entry point to leaf operations.

**Note**: Helper functions added for Norminette compliance (max 25 lines per function):
- `dispatch_ace()` — dispatches A/C/E elements in `dispatch_element()`
- `parse_camera_params()` — parses camera parameters in `parse_camera()`
- `parse_light_params()` — parses light parameters in `parse_light()`
- `parse_sphere_params()` — parses sphere parameters in `parse_sphere()`
- `parse_fraction()` — parses decimal part in `parse_double()`

**Note**: Core parsing functions are in `parser_utils.c` (parse_double, parse_vector3) and `parser_color.c` (parse_color_rgb with validation).

## Full parser call tree

```
main()
  └─> parse_scene_file(filename)
      ├─> init_parse_state(&scene, &state)
      │   └─> world_make()
      │
      ├─> open(filename, O_RDONLY)
      │   └─> [on error] → parser_error("Failed to open scene file", 0)
      │
      ├─> read_scene_file(fd, &scene, &state)
      │   └─> while (line = get_next_line_bonus(fd))
      │       ├─> state.line_num++
      │       │
      │       ├─> parse_single_line(line, &scene, &state)
      │       │   ├─> trimmed = ft_strtrim(line, " \t\n\r\v\f")
      │       │   │
      │       │   │   ├─> dispatch_element(trimmed, &scene, &state)
      │       │   │   │   ├─> [if line[0] == '#' or '\0'] → return true
      │       │   │   │   │
      │       │   │   │   ├─> dispatch_ace(line, &scene, &state)  [helper for A/C/E]
      │       │   │   │   │   │
      │       │   │   │   │   ├─> [if "A "] → parse_ambient(line, &scene)
      │       │   │   │   ├─> ptr = line + 2
      │       │   │   │   ├─> ratio = parse_double(&ptr)
      │       │   │   │   │   └─> skip whitespace, parse sign, int part, frac part
      │       │   │   │   ├─> color = parse_color_rgb(&ptr)
      │       │   │   │   │   ├─> R = parse_double(&ptr)
      │       │   │   │   │   ├─> G = parse_double(&ptr)
      │       │   │   │   │   ├─> B = parse_double(&ptr)
      │       │   │   │   │   └─> return color(R/255, G/255, B/255)
      │       │   │   │   ├─> scene->ambient_ratio = ratio
      │       │   │   │   ├─> scene->ambient_color = color
      │       │   │   │   └─> return true
      │       │   │   │
      │       │   │   ├─> [if "C "] → parse_camera(line, &scene)
      │       │   │   │   ├─> ptr = line + 2
      │       │   │   │   ├─> position = parse_vector3(&ptr)
      │       │   │   │   │   ├─> x = parse_double(&ptr)
      │       │   │   │   │   ├─> y = parse_double(&ptr)
      │       │   │   │   │   ├─> z = parse_double(&ptr)
      │       │   │   │   │   └─> return point(x, y, z)
      │       │   │   │   ├─> orientation = parse_vector3(&ptr)
      │       │   │   │   │   └─> normalize and clamp to [-1, 1]
      │       │   │   │   ├─> fov_degrees = parse_double(&ptr)
      │       │   │   │   ├─> fov_radians = fov_degrees * M_PI / 180
      │       │   │   │   ├─> scene->camera.position = position
      │       │   │   │   ├─> scene->camera.orientation = orientation
      │       │   │   │   ├─> scene->camera.field_of_view = fov_radians
      │       │   │   │   └─> return true
      │       │   │   │
      │       │   │   ├─> [if "L "] → parse_light(line, &scene)
      │       │   │   │   ├─> ptr = line + 2
      │       │   │   │   ├─> position = parse_vector3(&ptr)
      │       │   │   │   ├─> intensity = parse_double(&ptr)
      │       │   │   │   ├─> color = parse_color_rgb(&ptr)
      │       │   │   │   ├─> scene->world.light.position = position
      │       │   │   │   ├─> scene->world.light.intensity = intensity
      │       │   │   │   ├─> scene->world.light.color = color
      │       │   │   │   └─> return true
      │       │   │   │
      │       │   │   ├─> [if "sp "] → parse_sphere(line, &scene)
      │       │   │   │   ├─> ptr = line + 3
      │       │   │   │   ├─> center = parse_vector3(&ptr)
      │       │   │   │   ├─> diameter = parse_double(&ptr)
      │       │   │   │   ├─> [if diameter <= 0] → return false
      │       │   │   │   ├─> color = parse_color_rgb(&ptr)
      │       │   │   │   ├─> sphere = sphere_create()
      │       │   │   │   ├─> sphere.material.color = color
      │       │   │   │   ├─> sphere = apply_sphere_transform(sphere, center, diameter)
      │       │   │   │   │   ├─> radius = diameter / 2.0
      │       │   │   │   │   ├─> scale = scaling(radius, radius, radius)
      │       │   │   │   │   ├─> translate = translation(center.x, center.y, center.z)
      │       │   │   │   │   ├─> transform = mat_mul(translate, scale)
      │       │   │   │   │   └─> return sphere_set_transform(sphere, transform)
      │       │   │   │   └─> world_add_sphere(&scene->world, sphere)
      │       │   │   │       ├─> [if count >= MAX_OBJECTS] → return false
      │       │   │   │       ├─> world->spheres[count] = sphere
      │       │   │   │       ├─> world->spheres_count++
      │       │   │   │       └─> return true
      │       │   │   │
      │       │   │   └─> [otherwise] → return false
      │       │   │
      │       │   └─> [if result == false] → parser_error("Invalid identifier or scene format", line_num)
      │       │
      │       ├─> free(trimmed)
      │       └─> free(line)
      │
      ├─> close(fd)
      │
      ├─> validate_scene(&state)
      │   ├─> [if !state.has_ambient] → parser_error("Missing ambient light (A)", 0)
      │   ├─> [if !state.has_camera] → parser_error("Missing camera (C)", 0)
      │   └─> [if !state.has_light] → parser_error("Missing at least one light (L)", 0)
      │
      └─> return scene
```

## Simplified call tree by element type

### Ambient light parsing
```
parse_ambient(line, scene)
  ├─> parse_double(&ptr)       // ratio
  │   └─> skip_whitespace → parse sign → parse digits → parse fraction
  │
  └─> parse_color_rgb(&ptr)    // color
      ├─> parse_double(&ptr)   // R
      ├─> parse_double(&ptr)   // G
      ├─> parse_double(&ptr)   // B
      └─> normalize: (R/255, G/255, B/255)
```

### Camera parsing
```
parse_camera(line, scene)
  ├─> parse_vector3(&ptr)      // position
  │   ├─> parse_double(&ptr)   // x
  │   ├─> parse_double(&ptr)   // y
  │   └─> parse_double(&ptr)   // z
  │
  ├─> parse_vector3(&ptr)      // orientation
  │   └─> normalize + clamp [-1, 1]
  │
  └─> parse_double(&ptr)       // fov
      └─> convert to radians: fov * π / 180
```

### Light parsing
```
parse_light(line, scene)
  ├─> parse_vector3(&ptr)      // position
  ├─> parse_double(&ptr)       // intensity
  └─> parse_color_rgb(&ptr)    // color
```

### Sphere parsing (most complex)
```
parse_sphere(line, scene)
  ├─> parse_vector3(&ptr)      // center
  ├─> parse_double(&ptr)       // diameter
  ├─> [validate] diameter > 0
  ├─> parse_color_rgb(&ptr)    // color
  ├─> sphere_create()
  ├─> apply_sphere_transform(sphere, center, diameter)
  │   ├─> scaling(radius, radius, radius)
  │   ├─> translation(center.x, center.y, center.z)
  │   ├─> mat_mul(translate, scale)
  │   └─> sphere_set_transform(sphere, transform)
  │
  └─> world_add_sphere(&world, sphere)
      ├─> [check] count < MAX_OBJECTS
      ├─> world->spheres[count] = sphere
      └─> world->spheres_count++
```

## Error paths (where parser_error() is called)

```
parse_scene_file()
  ├─> open() fails
  │   └─> parser_error("Failed to open scene file", 0)
  │
  ├─> dispatch_element() returns false
  │   └─> parser_error("Invalid identifier or scene format", line_num)
  │
  └─> validate_scene() fails
      ├─> missing ambient (A)
      │   └─> parser_error("Missing ambient light (A)", 0)
      ├─> missing camera (C)
      │   └─> parser_error("Missing camera (C)", 0)
      └─> missing light (L)
          └─> parser_error("Missing at least one light (L)", 0)
```

## Helper function call depth

### parse_double (leaf function)
```
parse_double(&ptr)
  ├─> skip whitespace
  ├─> check sign (-)
  ├─> parse integer part
  ├─> [if '.'] parse fractional part
  └─> return result * sign
```

### parse_vector3 (calls parse_double 3x)
```
parse_vector3(&ptr)
  ├─> x = parse_double(&ptr)
  ├─> [skip ',']
  ├─> y = parse_double(&ptr)
  ├─> [skip ',']
  ├─> z = parse_double(&ptr)
  └─> return point(x, y, z)
```

### parse_color_rgb (calls parse_double 3x + normalize)
```
parse_color_rgb(&ptr)
  ├─> R = parse_double(&ptr)
  ├─> [skip ',']
  ├─> G = parse_double(&ptr)
  ├─> [skip ',']
  ├─> B = parse_double(&ptr)
  ├─> normalize: R/255, G/255, B/255
  ├─> clamp to [0, 1]
  └─> return color(r, g, b)
```

## Critical paths and hotspots

### Most frequently called functions
1. **parse_double** — called 3x per vector, 3x per color, 1x per scalar
   - For "sp 0,0,0 2.0 255,0,0": called 7 times
   - Performance critical: optimize whitespace skip, digit parsing

2. **parse_vector3** — called for every position/direction
   - Ambient: 0x
   - Camera: 2x (position + orientation)
   - Light: 1x (position)
   - Sphere: 1x (center)

3. **parse_color_rgb** — called for every colored element
   - Ambient: 1x
   - Camera: 0x
   - Light: 1x
   - Sphere: 1x

### Deepest call stacks
```
Depth 0: main()
Depth 1: parse_scene_file()
Depth 2: read_scene_file()
Depth 3: parse_single_line()
Depth 4: dispatch_element()
Depth 5: parse_sphere()
Depth 6: apply_sphere_transform()
Depth 7: mat_mul()
```

Maximum stack depth: 7 levels

## Debugging with call tree

### Issue: "Sphere not appearing"
Trace from bottom up:
1. `world_add_sphere` returns false? → world full (MAX_OBJECTS reached)
2. `apply_sphere_transform` wrong? → check scaling/translation matrices
3. `parse_sphere` returns false? → diameter <= 0
4. `parse_double` returns 0? → whitespace not skipped, parsing failed
5. `dispatch_element` not matching "sp "? → check identifier

### Issue: "Wrong colors"
Trace color path:
1. `parse_color_rgb` → check R,G,B values parsed correctly
2. Normalization (div by 255) → check not clamping too early
3. `scene->ambient_color` / `sphere.material.color` → check storage
4. Later: rendering uses normalized colors → should be 0-1

### Issue: "Camera not set"
Trace camera path:
1. `parse_camera` called? → check "C " identifier matched
2. FOV conversion → check degrees to radians (× π/180)
3. Orientation normalization → check not zero vector

## Comparison with other views

| View | File | Focus | When to use |
|------|------|-------|-------------|
| **Call Tree** | README.calltree.md | Function call hierarchy | Debugging execution flow, understanding algorithm structure |
| **Component** | README.components.md | File/module structure | Refactoring, adding features, code organization |
| **Flowchart** | README.md | Control flow (if/else/loops) | Understanding logic, branch coverage |
| **Sequence** | README.sequence.md | Object interactions | Tracing messages between modules |
| **Data Flow** | README.dataflow.md | Data transformations | Format debugging, unit conversion |

Tip: Use Call Tree for stack traces and performance profiling; use Component for architecture decisions.
