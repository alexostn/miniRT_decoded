ss# Parser Architecture — Component View

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
| parse_scene.c    |  | parse_internal.c  |  | parser_utils.c     |  | parse_validate.c   |
| (Orchestration)  |  | (Dispatch Logic)  |  | (Token Parsing)    |  | (Validation)       |
|------------------|  |-------------------|  |--------------------|  |--------------------|
| - parse_scene_   |  | - dispatch_       |  | - parse_double     |  | - validate_scene   |
|   file()         |  |   element()       |  | - parse_vector3    |  | - validate_range   |
| - read_scene_    |  | - init_parse_     |  | - is_valid_number_ |  | - validate_        |
|   file()         |  |   state()         |  |   end()            |  |   normalized       |
|                  |  | - parser_error()  |  | - parse_fraction() |  |                    |
|                  |  | - dispatch_ace()  |  |                    |  |                    |
+------------------+  +-------------------+  +--------------------+  +--------------------+
         |                     |                       ^                       ^
         |                     |                       |                       |
         |                     | (Dispatches to)       | (All use)             | (Called at end)
         V                     V                       |                       |
         |              +------+------+--------+-------+---+                   |
         |              |      |      |        |           |                   |
         |              V      V      V        V           V                   |
         |     +--------+  +--------+  +--------+  +-------------+            |
         |     | parse_ |  | parse_ |  | parse_ |  | parse_      |            |
         |     | ambient|  | camera |  | light  |  | sphere.c    |            |
         |     | .c     |  | .c     |  | .c     |  |             |            |
         |     |--------|  |--------|  |--------|  |-------------|            |
         |     | parse_ |  | parse_ |  | parse_ |  | parse_      |            |
         |     | ambient|  | camera |  | light  |  | sphere()    |            |
         |     | ()     |  | ()     |  | ()     |  | parse_      |            |
         |     |        |  |        |  |        |  | sphere_     |            |
         +---->+--------+  +--------+  +--------+  | params()    |            |
                    |           |           |       +-------------+            |
                    |           |           |              |                   |
                    +-----+-----+-----+-----+--------------+---+               |
                          |           |                        |               |
                          V           V                        V               |
                    Uses utils    Validates data       +----------------+      |
                          |           |                | parser_color.c |      |
                          |           |                |----------------|      |
                          |           |                | parse_color_   |      |
                          +-----------+--------------->| rgb()          |      |
                                                       | normalize_     |      |
                                                       | color_value()  |      |
                                                       +----------------+      |
                                                              |                |
                                                              +----------------+
                                                       
Note: parse_helpers.c (legacy) — Used only by tests, contains duplicate
      functions from parser_utils.c and parser_color.c
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
  - `dispatch_ace()`: helper for dispatching A/C elements (Norminette compliant)
  - `init_parse_state()`: initializes scene and tracking state
  - `parser_error()`: prints error and exits
  - **Dispatches to**: parse_ambient/camera/light/sphere
  - **Critical**: if dispatch logic wrong, parser calls wrong function

### Low-level token parsing
- **parser_utils.c** (Main project)
  - `parse_double()`: reads floating point with format validation
  - `parse_fraction()`: helper for parsing fractional part (Norminette split)
  - `parse_vector3()`: parses "x,y,z" format with sentinel value w=-1.0 on error
  - `is_valid_number_end()`: validates character after number
  - **Used by**: ALL element parsers
  - **Critical**: bugs here affect all parsing

- **parser_color.c** (Main project)
  - `parse_color_rgb()`: parses "R,G,B" (0-255) with range validation
  - `normalize_color_value()`: converts [0-255] → [0.0-1.0]
  - **Validates**: RGB must be in range [0-255], rejects out-of-range values
  - **Used by**: parse_ambient, parse_light, parse_sphere
  - **Critical**: ensures color values are valid before rendering

- **parse_helpers.c** (Tests only - legacy)
  - Contains duplicate functions for test compatibility
  - **Note**: Not used in main project, only in tests/Makefile
  - Kept synchronized with parser_utils.c and parser_color.c

### Scene validation
- **parse_validate.c**
  - `validate_scene()`: ensures required elements (A, C, L) exist
  - `validate_range()`: checks numeric values are within valid ranges
  - `validate_normalized()`: checks vectors are unit length
  - **Called by**: parse_scene.c at the end, element parsers during parsing
  - **Critical**: prevents incomplete or invalid scenes from rendering

### Element-specific parsers
- **parse_ambient.c**
  - `parse_ambient()`: parses "A ratio R,G,B"
  - Sets: `scene.ambient_ratio`, `scene.ambient_color`
  - Validates: ratio in range [0.0-1.0], RGB in [0-255]
  - Uses: parse_double (from parser_utils.c), parse_color_rgb (from parser_color.c)

- **parse_camera.c**
  - `parse_camera()`: parses "C x,y,z dx,dy,dz fov"
  - `parse_camera_params()`: helper function (Norminette <25 lines)
  - Sets: `scene.camera` with position, orientation, FOV
  - Validates: FOV in range [0-180], orientation is normalized
  - Converts: FOV degrees → radians
  - Uses: parse_vector3, parse_double, validate_range, validate_normalized

- **parse_light.c**
  - `parse_light()`: parses "L x,y,z intensity R,G,B"
  - `parse_light_params()`: helper function (Norminette <25 lines)
  - Sets: `scene.world.light` with position, intensity, color
  - Validates: intensity in [0.0-1.0], RGB in [0-255]
  - Uses: parse_vector3, parse_double, parse_color_rgb

- **parse_sphere.c**
  - `parse_sphere()`: parses "sp x,y,z diameter R,G,B"
  - `parse_sphere_params()`: helper function (Norminette <25 lines)
  - Creates sphere with material color
  - Validates: diameter > 0, RGB in [0-255]
  - Transforms: scales by radius, translates to center
  - Adds to: `world.spheres[]` via `world_add_sphere()`
  - Uses: parse_vector3, parse_double, parse_color_rgb
  - **Most complex**: involves geometry creation and transformation

## Dependency analysis

### Critical dependencies
```
parser_utils.c (core parsing)
    ↑
    | (Used by ALL element parsers)
    |
    +-- parse_ambient.c
    +-- parse_camera.c
    +-- parse_light.c
    +-- parse_sphere.c

parser_color.c (RGB parsing)
    ↑
    | (Used by parsers with colors)
    |
    +-- parse_ambient.c
    +-- parse_light.c
    +-- parse_sphere.c
```
- If `parser_utils.c` has a bug → ALL parsing fails
- If `parser_color.c` has a bug → ALL color parsing fails
- Changes to `parse_double` → retest ALL elements
- Changes to `parse_color_rgb` → retest ambient, light, sphere

**Note**: `parse_helpers.c` is legacy (tests only), not used in main project

### Call chain
```
main()
  → parse_scene_file()           [parse_scene.c]
      → read_scene_file()
          → dispatch_element()    [parse_internal.c]
              → dispatch_ace()    [parse_internal.c] (helper for A/C/E)
                  → parse_ambient()   [parse_ambient.c]
                  → parse_camera()    [parse_camera.c]
                      → parse_camera_params() [helper]
                  → parse_light()     [parse_light.c]
                      → parse_light_params() [helper]
              → parse_sphere()    [parse_sphere.c]
                  → parse_sphere_params() [helper]
                  → world_add_sphere() [world module]
      → validate_scene()          [parse_validate.c]
  → return scene
```

**Note**: Helper functions added for Norminette compliance (max 25 lines per function)

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
3. Use existing helpers from `parser_utils.c`: `parse_vector3`, `parse_double`
4. Use `parse_color_rgb` from `parser_color.c` if color is needed
5. Add plane to world storage
6. If function > 25 lines, create helper function (e.g., `parse_plane_params()`)

### New token type (e.g., range parsing)
1. Add function to `parser_utils.c`:
   ```c
   bool parse_range(char **str, double *min, double *max);
   ```
2. Ensure function stays under 25 lines (Norminette)
3. Use in element parsers as needed
4. Add corresponding unit test in `tests/test_parse.c`

### New validation rule (e.g., max sphere count)
1. Extend `validate_scene()` in `parse_validate.c`:
   ```c
   if (state->spheres_count > MAX_SPHERES)
       parser_error("Too many spheres", 0);
   ```
2. Ensure function stays under 25 lines (consider helper if needed)

## Code review checklist

- [ ] New parsing logic in correct file:
  - Core token parsing (double, vector3) → `parser_utils.c`
  - RGB color parsing → `parser_color.c`
  - Element dispatch → `parse_internal.c`
  - Specific element → `parse_<element>.c`
  - Validation → `parse_validate.c`
- [ ] Norminette compliance:
  - Functions max 25 lines
  - Max 5 functions per file
  - Max 80 columns per line
  - No ternary operators
  - Single tab between type and function name
- [ ] Unit tests added in `tests/test_parse.c` for new parsing functions
- [ ] Integration tests added in `scenes/` for new element types
- [ ] Documentation updated in `docs/parser/` diagrams
- [ ] Helper functions created if main function exceeds 25 lines

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
