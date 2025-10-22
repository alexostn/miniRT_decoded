# Parser Testing Guide

## Quick Test Commands

### 1. Test with a specific scene file

```bash
./miniRT scenes/test_parser_all.rt
```

### 2. Run automated parser tests

```bash
./test_parser.sh
```

### 3. Manual validation tests

```bash
# Valid scene (should work)
./miniRT scenes/valid_simple.rt

# Invalid scenes (should show error)
./miniRT scenes/invalid_id.rt
./miniRT scenes/no_camera.rt
./miniRT scenes/invalid_range_color.rt
```

---

## Test Scene Formats

### Complete Test Scene

File: `scenes/test_parser_all.rt`

```
# Ambient lighting
A 0.2 255,255,255

# Camera: position, orientation (normalized!), field of view
C 0,5,-10 0,0,1 70

# Light: position, brightness, color
L -5,10,0 0.7 255,255,255

# Sphere: center, diameter, color
sp 0,0,5 2 255,0,0

# Plane: point, normal vector (normalized!), color
pl 0,-1,0 0,1,0 100,100,100

# Cylinder: center, axis (normalized!), diameter, height, color
cy 3,0,5 0,1,0 1 4 0,255,0
```

---

## Parser Rules

### Required Elements
- ✅ Ambient light (A) - exactly once
- ✅ Camera (C) - exactly once  
- ✅ Light (L) - at least once

### Optional Elements
- Sphere (sp) - any number
- Plane (pl) - any number
- Cylinder (cy) - any number

### Important Notes

**Normalized Vectors Required:**
- Camera orientation vector **must be normalized**
- Plane normal vector **must be normalized**
- Cylinder axis vector **must be normalized**

**Color Format:**
- RGB values: 0-255
- Format: `R,G,B` (no spaces)

**Field of View:**
- Range: 0-180 degrees

---

## Test Scene Categories

### Valid Scenes
```
scenes/valid_simple.rt          - Basic valid scene
scenes/test_simple.rt           - Simple test case
scenes/test_parser_all.rt       - All object types
```

### Invalid Scenes (Error Testing)
```
scenes/invalid_id.rt            - Unknown identifier
scenes/invalid_range_color.rt   - Color out of range
scenes/invalid_range_fov.rt     - FOV out of range
scenes/no_camera.rt             - Missing camera
scenes/no_ambient.rt            - Missing ambient light
scenes/invalid_no_light.rt      - Missing light
```

---

## Parser Output

### Success
- Window opens
- Scene renders
- No error messages

### Failure
```
Error
Line X: <error description>
```

Common errors:
- `Invalid identifier or scene format`
- `Scene validation failed: Missing camera (C)`
- `Scene validation failed: Missing ambient light (A)`
- `Scene validation failed: Missing at least one light (L)`

---

## Debugging Parser

### Enable verbose mode (if implemented)
```bash
./miniRT scenes/test.rt --verbose
```

### Check specific line
Look at error message:
```
Error
Line 6: Invalid identifier or scene format
```

Then check line 6 in scene file:
```bash
sed -n '6p' scenes/test.rt
```

### Common Issues

**1. Vector not normalized**
```
# ❌ Wrong
C 0,5,-10 0,-0.5,1 70

# ✅ Correct
C 0,5,-10 0,0,1 70
```

**2. Missing space after identifier**
```
# ❌ Wrong
sp0,0,5 2 255,0,0

# ✅ Correct
sp 0,0,5 2 255,0,0
```

**3. Color format**
```
# ❌ Wrong
A 0.2 255, 255, 255
A 0.2 (255,255,255)

# ✅ Correct
A 0.2 255,255,255
```

---

## Integration with Tests

Run full test suite:
```bash
make run_test
```

This includes:
- ✅ 327 book tests (chapters 1-13)
- ✅ Ray tracing algorithms
- ✅ Geometry calculations
- ✅ Transformations
- ✅ Shadows and lighting

---

## Quick Checklist

Before pushing parser changes:

- [ ] `make` compiles without errors
- [ ] `make run_test` passes all 327 tests
- [ ] `./miniRT scenes/valid_simple.rt` works
- [ ] `./miniRT scenes/test_parser_all.rt` works
- [ ] Invalid scenes show appropriate errors
- [ ] All three object types render (sphere, plane, cylinder)
