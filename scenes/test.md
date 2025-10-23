# Parser Test Cases

## Valid Cases
L 0,10,0 0.7 255,255,255
### 1. Simple valid scene (valid_simple.rt) ✅
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,50,0 0.6 255,255,255
sp 0,0,20 12.6 255,0,0
```
**Expected**: Scene renders successfully

### 2. Scene with negative coordinates (test_negative.rt) ✅
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -10,10,-10 0.7 255,255,255
sp 0,0,20 12.6 255,0,0
```
**Expected**: Scene renders successfully with negative coordinates

## Invalid Cases

### 1. Missing required light (invalid_no_light.rt) ✅
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
sp 0,0,20 12.6 255,0,0
```
**Expected**: `Error\nScene validation failed: Missing at least one light (L)`
**Status**: ✅ Working - Light is required in miniRT

### 2. Invalid data type - letter in number (invalid_letter_in_number.rt) ✅
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -10,10,-10 0.7 255,255,255
sp 0,0,20 12.a 255,0,0
```
**Expected**: `Error\nLine 4: Invalid identifier or scene format`
**Status**: ✅ Working - Detects '12.a' as invalid number

### 3. Wrong amount of parameters - incomplete RGB (invalid_incomplete_color.rt) ✅
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,50,0 0.6 10,255
sp 0,0,20 12.6 255,0,0
```
**Expected**: `Error\nLine 3: Invalid identifier or scene format`
**Status**: ✅ Working - Detects incomplete color (needs R,G,B)

### 4. Missing sphere color (invalid_missing_sphere_color.rt) ✅
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,50,0 0.6 255,255,255
sp 0,0,20 12.6
```
**Expected**: `Error\nLine 4: Invalid identifier or scene format`
**Status**: ✅ Working - Detects missing color parameter

### 5. Invalid color range (invalid_range_color.rt) ✅
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,50,0 0.6 256,255,255
sp 0,0,20 12.6 255,0,0
```
**Expected**: `Error\nLine 3: Invalid identifier or scene format`
**Status**: ✅ Working - RGB values must be in range [0-255]

### 6. Invalid FOV range (invalid_range_fov.rt) ✅
```
A 0.2 255,255,255
C -50,0,20 0,0,1 181
L -40,50,0 0.6 255,255,255
sp 0,0,20 12.6 255,0,0
```
**Expected**: `Error\nLine 2: Invalid identifier or scene format`
**Status**: ✅ Working - FOV must be in range [0-180]

### 7. Invalid ambient range (invalid_range_ambient.rt) ✅
```
A 1.2 255,255,255
C -50,0,20 0,0,1 70
L -40,50,0 0.6 255,255,255
sp 0,0,20 12.6 255,0,0
```
**Expected**: `Error\nLine 1: Invalid identifier or scene format`
**Status**: ✅ Working - Ambient ratio must be in range [0.0-1.0]

### 8. Missing required element - no ambient (no_ambient.rt) ✅
```
C -50,0,20 0,0,1 70
L -40,50,0 0.6 255,255,255
sp 0,0,20 12.6 255,0,0
```
**Expected**: `Error\nScene validation failed: Missing ambient light (A)`
**Status**: ✅ Working

### 9. Missing required element - no camera (no_camera.rt) ✅
```
A 0.2 255,255,255
L -40,50,0 0.6 255,255,255
sp 0,0,20 12.6 255,0,0
```
**Expected**: `Error\nScene validation failed: Missing camera (C)`
**Status**: ✅ Working

### 10. Invalid identifier (invalid_id.rt) ✅
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,50,0 0.6 255,255,255
X 0,0,20 12.6 255,0,0
```
**Expected**: `Error\nLine 4: Invalid identifier or scene format`
**Status**: ✅ Working

### 11. Extra arguments (invalid_argc_extra.rt) ✅
```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,50,0 0.6 255,255,255 999
sp 0,0,20 12.6 255,0,0
```
**Expected**: `Error\nLine 3: Invalid identifier or scene format`
**Status**: ✅ Working - Extra argument '999' detected

## RGB Color Validation Details

### Color Behavior
**Question**: Are RGB values > 255 clamped or rejected?  
**Answer**: ✅ **REJECTED** (correct behavior for miniRT)

### Examples:
```bash
# Test: RGB 300 (out of range)
sp 0,0,20 10 255,300,0
# Result: Error - Line X: Invalid identifier or scene format

# Test: RGB 256 (out of range)  
sp 0,0,20 10 0,0,256
# Result: Error - Line X: Invalid identifier or scene format

# Test: RGB 255 (valid maximum)
sp 0,0,20 10 255,255,255
# Result: ✅ Accepted and rendered
```

### Implementation:
- RGB values are validated in `parse_color_rgb()`
- Valid range: [0-255]
- Out of range → returns error tuple (w=-1.0)
- Parser outputs "Error\n" and exits

### Why Not Clamping?
According to miniRT subject:
- "RGB colors: in range [0-255]"
- Values outside range = **invalid input**
- Must output "Error\n" (not silently clamp)
- This differs from projects like FdF where clamping is acceptable

## Test Results Summary

All validation cases work correctly ✅

- ✅ Format validation (letters in numbers)
- ✅ Range validation (ambient [0-1], FOV [0-180], RGB [0-255])
- ✅ Required elements validation (A, C, L must exist)
- ✅ Parameter count validation (check_end_of_line)
- ✅ Invalid identifiers detection
- ✅ Negative number parsing
- ✅ RGB out-of-range rejection (not clamping)