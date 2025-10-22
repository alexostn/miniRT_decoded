# Parser Validation Guide

## Overview

The miniRT parser validates all input according to the subject requirements. Invalid input results in `Error\n` output and program exit.

---

## Validation Rules

### Required Elements

Each scene **must** contain:
- **A** (Ambient light) - exactly once
- **C** (Camera) - exactly once
- **L** (Light) - at least once

Missing any required element → Error output

### Value Ranges

```
┌─────────────────────────────────────────────────────────────┐
│                     VALIDATION RANGES                       │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  RGB colors          → [0-255] (integer)                   │
│  Ambient ratio       → [0.0-1.0] (float)                   │
│  Light brightness    → [0.0-1.0] (float)                   │
│  Field of View (FOV) → [0-180] (degrees)                   │
│                                                             │
│  Normalized vectors  → Length must equal 1.0               │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

### Format Requirements

**Numbers:**
- Valid: `123`, `123.456`, `-123.456`
- Invalid: `12.a`, `1.2.3`, `abc`

**Colors (RGB):**
- Valid: `255,128,0`
- Invalid: `255, 128, 0` (spaces not allowed)
- Invalid: `255,300,0` (out of range)
- Invalid: `255,128` (incomplete)

**Vectors (x,y,z):**
- Valid: `0.0,1.0,0.0`
- Invalid: `0,1` (incomplete)

---

## Validation Layers

### 1. Format Validation

Functions: `parse_double()`, `parse_vector3()`, `parse_color_rgb()`

**Checks:**
- Valid number format
- No letters in numbers
- Correct delimiters (commas)

**Example:**
```c
// Valid
parse_double("123.45")    → 123.45

// Invalid - returns error
parse_double("12.a")      → Error
parse_double("1.2.3")     → Error
```

### 2. Range Validation

Function: `validate_range()`

**Checks:**
- Values within specified min/max
- Rejects (not clamps) out-of-range values

**Example:**
```c
validate_range(r, 0, 255)    // RGB: must be 0-255
validate_range(fov, 0, 180)  // FOV: must be 0-180
validate_range(ambient, 0, 1) // Ambient: must be 0.0-1.0
```

**Important:** Values outside range are **rejected**, not clamped!
- `256` in RGB → Error (not clamped to 255)
- This matches miniRT subject requirements

### 3. Vector Normalization

Function: `validate_normalized()`

**Checks:**
- Vector length ≈ 1.0 (with epsilon tolerance)
- Required for: camera orientation, plane normal, cylinder axis

**Example:**
```c
// Valid (length = 1.0)
validate_normalized(vector(0, 1, 0))     → true
validate_normalized(vector(1, 0, 0))     → true

// Invalid (length ≠ 1.0)
validate_normalized(vector(0, 0.5, 1))   → false
validate_normalized(vector(1, 1, 0))     → false
```

### 4. Argument Count Validation

Function: `check_end_of_line()`

**Checks:**
- No extra parameters
- All required parameters present

**Example:**
```c
// Valid
"sp 0,0,5 2.0 255,0,0"

// Invalid - extra parameter
"sp 0,0,5 2.0 255,0,0 extra"  → Error

// Invalid - missing parameter
"sp 0,0,5 2.0"                 → Error
```

### 5. Required Elements Check

Function: `validate_scene()`

**Called after parsing all lines**

Checks for:
- `has_ambient` - at least one A element
- `has_camera` - at least one C element  
- `has_light` - at least one L element

---

## Test Scenarios

### Valid Scenes ✅

```bash
# Basic valid scene
./miniRT scenes/valid_simple.rt

# Scene with negative coordinates
./miniRT scenes/test_negative.rt

# All object types
./miniRT scenes/test_parser_all.rt
```

### Invalid Scenes ❌

All should output `Error\n`:

```bash
# Missing required elements
./miniRT scenes/invalid_no_light.rt     # Missing L
./miniRT scenes/no_camera.rt            # Missing C
./miniRT scenes/no_ambient.rt           # Missing A

# Invalid ranges
./miniRT scenes/invalid_range_color.rt  # RGB > 255
./miniRT scenes/invalid_range_fov.rt    # FOV > 180
./miniRT scenes/invalid_range_ambient.rt # Ambient > 1.0

# Invalid formats
./miniRT scenes/invalid_letter_in_number.rt  # "12.a"
./miniRT scenes/invalid_incomplete_color.rt  # "255,128"
./miniRT scenes/invalid_format_color.rt      # Wrong format

# Wrong parameter count
./miniRT scenes/invalid_argc_extra.rt    # Too many
./miniRT scenes/invalid_argc_missing.rt  # Too few
./miniRT scenes/invalid_missing_sphere_color.rt

# Unknown identifier
./miniRT scenes/invalid_id.rt  # "X" instead of "sp"
```

---

## Running Validation Tests

### Automated Test Script

```bash
./test_parser_validation.sh
```

Expected output:
```
Valid scene tests:
✅ scenes/valid_simple.rt
✅ scenes/test_negative.rt

Invalid scene tests:
✅ scenes/invalid_no_light.rt
✅ scenes/invalid_range_color.rt
...
Results: 16/16 tests passed
```

### Manual Testing

```bash
# Valid scene - should open window
./miniRT scenes/valid_simple.rt

# Invalid scene - should print Error
./miniRT scenes/invalid_range_color.rt
# Output: Error
#         Line X: Invalid identifier or scene format
```

---

## RGB Validation: Important Note

### Correct Behavior

**RGB values outside [0-255] are REJECTED, not clamped**

This is the **correct** behavior according to miniRT subject:
> RGB colors: in range [0-255]

### Examples

```bash
# Test 1: RGB = 256 → Rejected
echo "A 0.2 256,255,255" > /tmp/test.rt
./miniRT /tmp/test.rt
# Output: Error

# Test 2: RGB = 300 → Rejected  
echo "sp 0,0,5 2 255,300,0" > /tmp/test.rt
./miniRT /tmp/test.rt
# Output: Error

# Test 3: RGB = 255 → Accepted
echo "A 0.2 255,255,255
C 0,0,0 0,0,1 70
L 0,5,0 0.7 255,255,255
sp 0,0,5 2 255,255,0" > /tmp/test.rt
./miniRT /tmp/test.rt
# Output: Window opens
```

### Why Not Clamp?

**Reason:** miniRT subject requires **error handling** for invalid input.

**Comparison with other 42 projects:**
- **FdF/fract-ol**: Clamping acceptable (visualization)
- **miniRT**: Strict validation (ray tracing precision)
- **cub3D**: Strict validation (game requirements)

**Evaluation:** Silently clamping values = loss of points!

---

## Implementation Files

```
src/parser/
├── parse_scene.c           # Main parsing loop
├── parse_internal.c        # Element dispatcher
├── parse_ambient.c         # A element
├── parse_camera.c          # C element
├── parse_light.c           # L element
├── parse_sphere.c          # sp element
├── parse_plane.c           # pl element
├── parse_cylinder.c        # cy element
├── parser_utils.c          # parse_double, parse_vector3
├── parser_color.c          # parse_color_rgb
└── parse_validate.c        # validate_range, validate_normalized
```

---

## Error Messages

### Standard Error Format

```
Error
Line X: <error description>
```

### Common Error Messages

```
Invalid identifier or scene format
Scene validation failed: Missing ambient light (A)
Scene validation failed: Missing camera (C)
Scene validation failed: Missing at least one light (L)
```

---

## Validation Summary

```
┌─────────────────────────────────────────────────────────────┐
│                  VALIDATION CHECKLIST                       │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ✓ Format validation      - Numbers, colors, vectors       │
│  ✓ Range validation       - RGB, FOV, ambient, brightness  │
│  ✓ Normalization check    - Camera, plane, cylinder        │
│  ✓ Argument count         - No extra/missing parameters    │
│  ✓ Required elements      - A, C, L present                │
│  ✓ Unknown identifiers    - Rejected                       │
│                                                             │
│  Result: All input validated before rendering              │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

## Testing Checklist

Before defense:

- [ ] `./miniRT scenes/valid_simple.rt` - works
- [ ] `./miniRT scenes/test_parser_all.rt` - works
- [ ] Invalid scenes output `Error\n`
- [ ] RGB > 255 rejected (not clamped)
- [ ] Missing A/C/L detected
- [ ] All 16 validation tests pass

**Status: ✅ All validation tests passing (16/16)**
