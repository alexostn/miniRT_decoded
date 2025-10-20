# miniRT Parser Validation Tests

## Overview

This document explains the parser validation system and confirms that all test cases work correctly.

## Test Results

✅ **All 16 validation tests pass**

### Valid Scenes (2 tests)
- ✅ Simple valid scene with all required elements
- ✅ Scene with negative coordinates

### Invalid Scenes (14 tests)
All correctly detected and output `Error\n`:

1. ✅ Missing required light (L)
2. ✅ Letter in number (e.g., `12.a`)
3. ✅ Incomplete RGB color (e.g., `10,255` instead of `R,G,B`)
4. ✅ Missing sphere color
5. ✅ RGB out of range [0-255]
6. ✅ FOV out of range [0-180]
7. ✅ Ambient ratio out of range [0-1]
8. ✅ Missing ambient light (A)
9. ✅ Missing camera (C)
10. ✅ Invalid identifier (e.g., `X` instead of `sp`)
11. ✅ Extra arguments
12. ✅ Missing arguments
13. ✅ Invalid format with letters
14. ✅ Invalid color format

## Running Tests

### Quick Test
```bash
./test_parser_validation.sh
```

### Manual Testing
```bash
# Valid scene (should render or timeout)
timeout 1 ./miniRT scenes/valid_simple.rt

# Invalid scene (should output "Error\n")
./miniRT scenes/invalid_no_light.rt
```

## Answers to Your Questions

### 1. "I don't have a scene without light or should it be like this?"

**Answer**: Yes, that's correct! In miniRT, light (L) is **required**.

Parser checks presence of all required elements:
- **A** (Ambient light) - required
- **C** (Camera) - required  
- **L** (Light) - required
- **sp/pl/cy** (Objects) - optional

File `scenes/invalid_no_light.rt` was created specifically to test this validation.

**Test result**:
```bash
./miniRT scenes/invalid_no_light.rt
# Output: Error
#         Scene validation failed: Missing at least one light (L)
```

**Conclusion**: In miniRT **all three required elements** (A, C, L) **are mandatory**.

Test `scenes/no_camera.rt` was also created:
```bash
./miniRT scenes/no_camera.rt
# Output: Error
#         Scene validation failed: Missing camera (C)
```

### 2. "Invalid data type and wrong amount of parameters are not checked"

**Answer**: Actually both checks **work correctly**!

#### Invalid data type check (letters in numbers):
```bash
./miniRT scenes/invalid_letter_in_number.rt
# File contains: sp 0,0,20 12.a 255,0,0
# Output: Error
#         Line 4: Invalid identifier or scene format
```
Function `parse_double()` checks `is_valid_number_end()` after parsing number.

#### Parameter count check:
```bash
./miniRT scenes/invalid_incomplete_color.rt
# File contains: L -40,50,0 0.6 10,255
# Output: Error
#         Line 3: Invalid identifier or scene format
```

```bash
./miniRT scenes/invalid_missing_sphere_color.rt
# File contains: sp 0,0,20 12.6
# Output: Error
#         Line 4: Invalid identifier or scene format
```

## Test Files Created

All test files are in `scenes/` directory:

**Valid**:
- `valid_simple.rt` - Basic valid scene
- `test_negative.rt` - Scene with negative coordinates

**Invalid**:
- `invalid_no_light.rt` - Missing light
- `invalid_letter_in_number.rt` - Contains `12.a`
- `invalid_incomplete_color.rt` - RGB with only 2 components
- `invalid_missing_sphere_color.rt` - Sphere without color
- `invalid_range_color.rt` - RGB value > 255
- `invalid_range_fov.rt` - FOV > 180
- `invalid_range_ambient.rt` - Ambient > 1.0
- `no_ambient.rt` - Missing ambient
- `no_camera.rt` - Missing camera
- `invalid_id.rt` - Unknown identifier
- `invalid_argc_extra.rt` - Too many arguments
- `invalid_argc_missing.rt` - Too few arguments
- `invalid_format_letter.rt` - Letter in number format
- `invalid_format_color.rt` - Invalid color format

## Implementation Details

### Validation Layers

1. **Format Validation** (`parse_double`, `parse_vector3`, `parse_color_rgb`)
   - Checks for valid number format
   - Detects letters in numbers
   - Uses `is_valid_number_end()` to verify correct endings

2. **Range Validation** (`validate_range`)
   - Ambient: [0.0 - 1.0]
   - FOV: [0 - 180]
   - RGB: [0 - 255]

3. **Argument Count Validation** (`check_end_of_line`)
   - Ensures no extra parameters
   - Detects missing parameters

4. **Required Elements Validation** (`validate_scene`)
   - Checks for presence of A, C, L

5. **Identifier Validation** (`dispatch_element`)
   - Returns false for unknown identifiers

## Conclusion

✅ All three issues you mentioned **already work correctly**:

1. ✅ Scene without light (L) - correctly outputs error
2. ✅ Scene without camera (C) - correctly outputs error
3. ✅ Invalid data type (letters in numbers) - detected
4. ✅ Wrong number of parameters - detected
5. ✅ RGB outside [0-255] range - rejected (not clamped)

Parser is fully functional and passes all 16 test scenarios!
