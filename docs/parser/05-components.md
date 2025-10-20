# Parser Architecture — Component View

This diagram shows the structure of the parser module: files, their responsibilities, and dependencies.

## Parser module structure

```
                    +-------------------------+
                    |       parser.h          |
                    |  (Core Interface)       |
                    | - t_scene               |
                    | - t_parse_state         |
                    | - Function Prototypes   |
                    +-------------------------+
                             |
                             | (Included by all parser .c files)
     +-----------------------+-----------------------+-----------------------+
     |                       |                       |                       |
     V                       V                       V                       V

+------------------+  +-------------------+  +--------------------+  +--------------------+
| parse_scene.c    |  | parse_internal.c  |  | parse_helpers.c    |  | parse_validate.c   |
| (Orchestration)  |  | (Dispatch Logic)  |  | (Token Parsing)    |  | (Validation)       |
|------------------|  |-------------------|  |--------------------|  |--------------------|
| - parse_scene_   |  | - dispatch_       |  | - parse_double     |  | - validate_scene   |
|   file()         |  |   element()       |  | - parse_vector3    |  |                    |
| - read_scene_    |  | - init_parse_     |  | - parse_color_rgb  |  |                    |
|   file()         |  |   state()         |  |                    |  |                    |
|                  |  | - parser_error()  |  |                    |  |                    |
+------------------+  +-------------------+  +--------------------+  +--------------------+
         |                     |                       ^                       ^
         |                     |                       |                       |
         |                     | (Dispatches to)       | (All use)             | (Called at end)
         V                     V                       |                       |
         |              +------+------+--------+-------+                       |
         |              |      |      |        |                               |
         |              V      V      V        V                               |
         |     +--------+  +--------+  +--------+  +-------------+            |
         |     | parse_ |  | parse_ |  | parse_ |  | parse_      |            |
         |     | ambient|  | camera |  | light  |  | sphere.c    |            |
         |     | .c     |  | .c     |  | .c     |  |             |            |
         |     |--------|  |--------|  |--------|  |-------------|            |
         |     | parse_ |  | parse_ |  | parse_ |  | parse_      |            |
         |     | ambient|  | camera |  | light  |  | sphere()    |            |
         |     | ()     |  | ()     |  | ()     |  | apply_      |            |
         |     |        |  |        |  |        |  | sphere_     |            |
         +---->+--------+  +--------+  +--------+  | transform() |            |
                    |           |           |       +-------------+            |
                    |           |           |              |                   |
                    +-----+-----+-----+-----+--------------+                   |
                          |           |                                        |
                          V           V                                        |
                    Uses helpers   Validates data                              |
                          |           |                                        |
                          +-----------+----------------------------------------+
```

## Component responsibilities

### Core orchestration
- **parse_scene.c**
  - Main entry point: `parse_scene_file(filename)`
  - File I/O: open, read loop with `get_next_line`, close
  - Line processing: trim whitespace, call dispatcher
  - Final validation and return scene
  - **Calls**: parse_internal (dispatch), parse_validate
  - **Critical**: if broken, nothing works

### Routing and error handling
- **parse_internal.c**
  - `dispatch_element()`: routes line to correct parser based on identifier
  - `init_parse_state()`: initializes scene and tracking state
  - `parser_error()`: prints error and exits
  - **Dispatches to**: parse_ambient/camera/light/sphere
  - **Critical**: if dispatch logic wrong, parser calls wrong function

### Low-level token parsing
- **parse_helpers.c**
  - `parse_double()`: reads floating point (with whitespace skip)
  - `parse_vector3()`: parses "x,y,z" format
  - `parse_color_rgb()`: parses "R,G,B" (0-255) and normalizes to 0-1
  - **Used by**: ALL element parsers
  - **Critical**: bugs here affect all parsing

### Scene validation
- **parse_validate.c**
  - `validate_scene()`: ensures required elements (A, C, L) exist
  - **Called by**: parse_scene.c at the end
  - **Critical**: prevents incomplete scenes from rendering

### Element-specific parsers
- **parse_ambient.c**
  - `parse_ambient()`: parses "A ratio R,G,B"
  - Sets: `scene.ambient_ratio`, `scene.ambient_color`
  - Uses: parse_double, parse_color_rgb

- **parse_camera.c**
  - `parse_camera()`: parses "C x,y,z dx,dy,dz fov"
  - Sets: `scene.camera.position/orientation/field_of_view`
  - Converts: FOV degrees → radians
  - Uses: parse_vector3, parse_double

- **parse_light.c**
  - `parse_light()`: parses "L x,y,z intensity R,G,B"
  - Sets: `scene.world.light.position/intensity/color`
  - Uses: parse_vector3, parse_double, parse_color_rgb

- **parse_sphere.c**
  - `parse_sphere()`: parses "sp x,y,z diameter R,G,B"
  - Creates sphere with material color
  - `apply_sphere_transform()`: scales by radius, translates to center
  - Validates: diameter > 0
  - Adds to: `world.spheres[]` via `world_add_sphere()`
  - Uses: parse_vector3, parse_double, parse_color_rgb
  - **Most complex**: involves geometry creation and transformation

## Dependency analysis

### Critical dependencies
```
parse_helpers.c
    ↑
    | (Used by ALL)
    |
    +-- parse_ambient.c
    +-- parse_camera.c
    +-- parse_light.c
    +-- parse_sphere.c
```
- If `parse_helpers.c` has a bug → ALL parsing fails
- Changes to `parse_double` → retest ALL elements

### Call chain
```
main()
  → parse_scene_file()           [parse_scene.c]
      → read_scene_file()
          → dispatch_element()    [parse_internal.c]
              → parse_ambient()   [parse_ambient.c]
              → parse_camera()    [parse_camera.c]
              → parse_light()     [parse_light.c]
              → parse_sphere()    [parse_sphere.c]
                  → world_add_sphere() [world module]
      → validate_scene()          [parse_validate.c]
  → return scene
```

### Error paths
```
parse_scene.c
  → open() fails → parser_error("Failed to open")
  → dispatch_element() returns false → parser_error("Invalid identifier")
  → validate_scene() fails → parser_error("Scene validation failed")
```

## Adding new features

### New element type (e.g., plane "pl")
1. Create `parse_plane.c` with `parse_plane()` function
2. Add case in `dispatch_element()` (parse_internal.c):
   ```c
   if (ft_strncmp(line, "pl ", 3) == 0)
       return (parse_plane((char *)line, scene));
   ```
3. Use existing helpers: `parse_vector3`, `parse_color_rgb`
4. Add plane to world storage

### New token type (e.g., range parsing)
1. Add function to `parse_helpers.c`:
   ```c
   bool parse_range(char **str, double *min, double *max);
   ```
2. Use in element parsers as needed

### New validation rule (e.g., max sphere count)
1. Extend `validate_scene()` in `parse_validate.c`:
   ```c
   if (state->spheres_count > MAX_SPHERES)
       parser_error("Too many spheres", 0);
   ```

## Code review checklist

- [ ] New parsing logic in correct file:
  - Token parsing → `parse_helpers.c`
  - Element dispatch → `parse_internal.c`
  - Specific element → `parse_<element>.c`
  - Validation → `parse_validate.c`

- [ ] Dependencies correct:
  - Element parsers use helpers (don't duplicate logic)
  - Error handling goes through `parser_error()`
  - State tracking updated in `parse_internal.c`

- [ ] Testing coverage:
  - New helper → test in ALL elements
  - New element → test valid/invalid/edge cases
  - New validation → test missing/duplicate scenarios

## Comparison with other views

| View | File | Focus | When to use |
|------|------|-------|-------------|
| **Component** | README.components.md | File structure, dependencies | Adding features, refactoring |
| **Flowchart** | README.md | Control flow (if/else/loops) | Understanding logic, debugging |
| **Swimlane** | README.swimlane.md | Module responsibilities | Seeing boundaries |
| **Sequence** | README.sequence.md | Interaction timeline | Tracing execution |
| **Data Flow** | README.dataflow.md | Data transformations | Format debugging |

Tip: use Component view for architecture decisions, Flowchart for debugging logic.
