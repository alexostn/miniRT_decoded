# Memory Cleanup Implementation

## Changes Summary

### 1. Enhanced Parser State Structure
Added cleanup tracking to `t_parse_state`:
- `int fd` - File descriptor to close on error
- `char *current_line` - Current line buffer to free
- `char *current_trimmed` - Trimmed line buffer to free

### 2. New Error Handler with Cleanup
Created `parser_error_cleanup()` function that:
- Frees `current_trimmed` if allocated
- Frees `current_line` if allocated  
- Closes `fd` if open
- Then exits with error message

### 3. Updated Parser Flow
Modified `parse_scene.c` to track resources:
- Store `fd` in state
- Track `current_line` and `current_trimmed` pointers
- Set to NULL after freeing
- Use `parser_error_cleanup()` for all parsing errors

### 4. Systematic Replacement
Replaced all `parser_error()` calls with `parser_error_cleanup()` in:
- `src/parser/*.c` (common parsers)
- `src/mandatory/parser/*.c` (mandatory-specific)
- `src/bonus/parser/*.c` (bonus-specific)

## Testing

### Before Changes
```bash
# Error case showed leaks:
==42798== still reachable: 90 bytes in 3 blocks
   27 bytes → ft_strtrim
   28 bytes → get_next_line buffer  
   35 bytes → get_next_line buffer
```

### After Changes
```bash
# Run test with invalid scene (mandatory binary, bonus scene):
make
./miniRT scenes/valid_scenes/complex_multi_light.rt

# Expected: Clean exit with 0 bytes leaked
```

## Valgrind Test Commands

### Test successful execution (no leaks expected):
```bash
make
make run SCENE=scenes/valid_scenes/basic_shape_sphere.rt V=1
```

### Test error handling (should now also have 0 leaks):
```bash  
make
./miniRT scenes/valid_scenes/complex_multi_light.rt
# (This scene has multiple lights, error in mandatory)
```

### Test with bonus:
```bash
make bonus
make run SCENE=scenes/valid_scenes/complex_multi_light.rt V=1
```

## Results

Both success and error cases should now show:
```
definitely lost: 0 bytes
still reachable: 0 bytes (or only MLX internals)
```

## Notes

- `parser_error()` still exists for errors without state context
- `parser_error_cleanup()` used for all parsing errors with state
- GNL buffers are now tracked and freed on error
- File descriptors are properly closed on error

