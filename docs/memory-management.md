# Memory Management & Debugging

This document provides stack trace diagrams for common memory leaks in miniRT and how to debug them.

## Understanding Stack Traces

A **Stack Trace Diagram** shows the execution path from your entry point (`main`) to where memory is allocated but not freed. It helps identify:
- Where memory leaks occur
- Responsibility boundaries (your code vs library code)
- What cleanup functions to call

Reading the diagram:
- **Bottom (root)**: Entry point (`main()`)
- **Middle**: Your function calls
- **Dashed line**: Boundary between your code (below) and library code (above)
- **Top (leaf)**: Actual memory allocation (`malloc`/`calloc`)

## Common Memory Leaks in miniRT

### 1. MLX Image Leak

```
        ^  Memory allocation (top of stack)
        |
   [ calloc ]  <-- Memory allocated here, pointer lost
        ^
        |
  /-----+-----------------------------------\
 /      |                                     \
| [ mlx_int_new_xshm_image ]  <-- MLX internal | [ mlx_init ]  <-- MLX initialization
|     (MLX Library)           |                | (MLX Library)
|           ^                 |                |
|           |                 |                |
|     [ mlx_new_image ]       |                |
|     (MLX Library)           |                |
 \          ^                 /                /
  \---------+----------------/                /
            |                                 /
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
^ ^ ^ ^ ^ ^ |  Responsibility boundary: above - library code,   ^ ^ ^ ^ ^
            |  which you don't control. Below - your code.      |
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
            |                                 |
      [ image_create ] <--- (YOUR CODE)       |
      (image.c:42)                            |
            ^                                 |
            |                                 |
      +-----+---------------------------------+
      |
[ main ] <------------------------------------ (YOUR CODE, entry point)
```

**Problem**: `mlx_new_image()` allocates memory internally, but you never call `mlx_destroy_image()`.

**Solution**:
```c
// In your cleanup function:
if (data->img)
    mlx_destroy_image(data->mlx, data->img);
if (data->mlx)
{
    mlx_destroy_display(data->mlx);  // Linux only
    free(data->mlx);
}
```

**Valgrind output**:
```
==12345== 1,024 bytes in 1 blocks are definitely lost
==12345==    at calloc (vg_replace_malloc.c:752)
==12345==    by mlx_int_new_xshm_image (in /usr/lib/libmlx.a)
==12345==    by mlx_new_image (in /usr/lib/libmlx.a)
==12345==    by image_create (image.c:42)
==12345==    by main (main.c:15)
```

### 2. Parser String Leak

```
        ^  Memory allocation
        |
   [ malloc ]  <-- Memory allocated for trimmed string
        ^
        |
  [ ft_strtrim ]  <-- Allocates new string
  (libft)
        ^
        |
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
^ ^ ^ ^ ^ |  Boundary: libft (above) vs parser (below)  ^ ^ ^ ^ ^
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        |
  [ parse_single_line ]  <-- Trimmed string not freed on error path
  (parse_scene.c:19)
        ^
        |
  [ read_scene_file ]
  (parse_scene.c:32)
        ^
        |
  [ parse_scene_file ]
  (parse_scene.c:48)
        ^
        |
  [ main ]
```

**Problem**: `ft_strtrim()` allocates memory for trimmed string, but it's not freed when `dispatch_element()` returns false and `parser_error()` is called.

**Solution**:
```c
static bool parse_single_line(char *line, t_scene *sc, t_parse_state *st)
{
    char *trimmed;
    bool result;

    trimmed = ft_strtrim(line, " \t\n\r\v\f");
    if (!trimmed)
        parser_error("Memory allocation failed during trim", st->line_num);
    result = dispatch_element(trimmed, sc, st);
    free(trimmed);  // ← Always free before error exit
    if (!result)
        parser_error("Invalid identifier or scene format", st->line_num);
    return (result);
}
```

### 3. Sphere Array Reallocation Leak (Future: Heap-based World)

```
        ^  Memory allocation
        |
   [ realloc ]  <-- Old array not freed properly
        ^
        |
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
^ ^ ^ ^ ^ |  Boundary: standard library vs your code  ^ ^ ^ ^ ^ ^
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        |
  [ world_add_sphere ]  <-- Realloc call here
  (world_add_object.c:35)
        ^
        |
  [ parse_sphere ]
  (parse_sphere.c:60)
        ^
        |
  [ dispatch_element ]
  (parse_internal.c:52)
        ^
        |
  [ parse_scene_file ]
        ^
        |
  [ main ]
```

**Problem**: When switching to heap-based world (dynamic sphere array), forgetting to free old array after `realloc()`.

**Wrong approach**:
```c
// DON'T DO THIS:
bool world_add_sphere(t_world *world, t_sphere sphere)
{
    t_sphere *new_array;
    
    if (world->spheres_count >= world->capacity)
    {
        new_array = realloc(world->spheres, world->capacity * 2);
        // ← If realloc fails, world->spheres is still valid but lost!
        world->spheres = new_array;
        world->capacity *= 2;
    }
    world->spheres[world->spheres_count++] = sphere;
    return (true);
}
```

**Correct approach**:
```c
bool world_add_sphere(t_world *world, t_sphere sphere)
{
    t_sphere *new_array;
    
    if (world->spheres_count >= world->capacity)
    {
        new_array = realloc(world->spheres, sizeof(t_sphere) * world->capacity * 2);
        if (!new_array)
            return (false);  // Keep old array valid
        world->spheres = new_array;
        world->capacity *= 2;
    }
    world->spheres[world->spheres_count++] = sphere;
    return (true);
}
```

### 4. Get Next Line Buffer Leak

```
        ^  Memory allocation
        |
   [ malloc ]  <-- Line buffer allocated
        ^
        |
  [ get_next_line_bonus ]  <-- Returns allocated string
  (get_next_line.c)
        ^
        |
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
^ ^ ^ ^ ^ |  Boundary: GNL vs parser  ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^ ^
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        |
  [ read_scene_file ]  <-- Line must be freed each iteration
  (parse_scene.c:35)
        ^
        |
  [ parse_scene_file ]
        ^
        |
  [ main ]
```

**Problem**: Each call to `get_next_line_bonus()` returns a newly allocated string that must be freed.

**Solution**:
```c
static void read_scene_file(int fd, t_scene *sc, t_parse_state *st)
{
    char *line;

    line = get_next_line_bonus(fd);
    while (line)
    {
        st->line_num++;
        parse_single_line(line, sc, st);
        free(line);  // ← Free each line after processing
        line = get_next_line_bonus(fd);
    }
}
```

## Debugging Workflow

### Step 1: Run Valgrind
```bash
# Linux only
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --suppressions=mlx.supp \
         ./miniRT scenes/test.rt
```

### Step 2: Read Stack Trace
Example output:
```
==12345== 128 bytes in 1 blocks are definitely lost in loss record 5 of 10
==12345==    at malloc (vg_replace_malloc.c:299)
==12345==    by ft_strtrim (ft_strtrim.c:42)
==12345==    by parse_single_line (parse_scene.c:19)
==12345==    by read_scene_file (parse_scene.c:35)
==12345==    by parse_scene_file (parse_scene.c:52)
==12345==    by main (main.c:25)
```

### Step 3: Draw Stack Trace Diagram
Convert Valgrind output to visual diagram (see examples above).

### Step 4: Identify Responsibility Boundary
- **Above boundary**: Library code (MLX, libft, libc) — you can't modify
- **Below boundary**: Your code — where you add cleanup

### Step 5: Add Cleanup
```c
// Example cleanup structure
typedef struct s_cleanup
{
    t_mlx    *mlx;
    t_img    *img;
    t_world  *world;
    int      fd;
}   t_cleanup;

void cleanup_all(t_cleanup *cleanup)
{
    if (cleanup->fd >= 0)
        close(cleanup->fd);
    if (cleanup->world)
        free_world(cleanup->world);
    if (cleanup->img)
        mlx_destroy_image(cleanup->mlx, cleanup->img);
    if (cleanup->mlx)
    {
        mlx_destroy_display(cleanup->mlx);
        free(cleanup->mlx);
    }
}
```

## Memory Management Best Practices

### 1. Free in Reverse Order of Allocation
```c
// Allocation order:
mlx = mlx_init();               // 1
img = mlx_new_image(mlx, ...);  // 2
world = init_world();           // 3

// Free in reverse:
free_world(world);              // 3
mlx_destroy_image(mlx, img);    // 2
mlx_destroy_display(mlx);       // 1
free(mlx);
```

### 2. NULL-check Before Free
```c
if (ptr)
{
    free(ptr);
    ptr = NULL;  // Prevent double-free
}
```

### 3. Use Cleanup Functions
```c
// Good: centralized cleanup
void free_world(t_world *world)
{
    if (!world)
        return;
    if (world->spheres)
        free(world->spheres);
    if (world->planes)
        free(world->planes);
    // ... free other resources
}
```

### 4. Error Paths Must Free
```c
t_scene *parse_scene_file(const char *filename)
{
    int fd;
    t_scene *scene;

    scene = malloc(sizeof(t_scene));
    if (!scene)
        return (NULL);
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        free(scene);  // ← Don't forget on error path
        return (NULL);
    }
    
    // ... rest of parsing
    close(fd);
    return (scene);
}
```

## Testing for Leaks

### Automated Testing
```bash
# Run all tests with Valgrind
make test-all-valgrind

# Check specific test
cd tests
valgrind --leak-check=full ./test_parser_simple
```

### Expected Output (No Leaks)
```
==12345== HEAP SUMMARY:
==12345==     in use at exit: 0 bytes in 0 blocks
==12345==   total heap usage: 45 allocs, 45 frees, 8,192 bytes allocated
==12345== 
==12345== All heap blocks were freed -- no leaks are possible
```

### Suppressing MLX Internal Leaks
Some MLX internals may show false positives. Use suppression file:

**mlx.supp**:
```
{
   mlx_init_leak
   Memcheck:Leak
   ...
   fun:mlx_init
}
{
   mlx_xshm_leak
   Memcheck:Leak
   ...
   fun:mlx_int_new_xshm_image
}
```

Usage:
```bash
valgrind --suppressions=mlx.supp ./miniRT scene.rt
```

## See Also
- [Parser Architecture](../parser/) — Understanding parser structure
- [Parser Call Tree](../parser/06-calltree.md) — Function call hierarchy
- Main README — Project setup and testing

## Quick Reference

| Leak Type | Cleanup Function | When to Call |
|-----------|------------------|--------------|
| MLX context | `mlx_destroy_display()`, `free()` | Before program exit |
| MLX image | `mlx_destroy_image()` | When image no longer needed |
| MLX window | `mlx_destroy_window()` | When closing window |
| GNL line | `free()` | After each `get_next_line()` call |
| ft_strtrim | `free()` | After using trimmed string |
| Scene/World | Custom `free_world()` | Before program exit |
| File descriptor | `close()` | After reading file |

## See Also
- [Parser Architecture](parser/README.md) — understand parser structure before debugging
- [Architecture Comparison](architecture-comparison.md) — stack vs heap vs hybrid benchmark
- [Hybrid Heap Transition](hybrid-heap-transition.md) — recommended scalability approach
- [Hybrid Architecture Flowchart](hybrid-architecture-flowchart.md) — visual diagrams
- [Full Heap Migration](heap-transition.md) — alternative architecture

---

*Part of miniRT documentation. For parser-specific docs, see [docs/parser/](../parser/).*
