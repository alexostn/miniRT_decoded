# miniRT Documentation Summary

## 📁 Documentation Structure

```
docs/
├── parser/                          # Parser module documentation
│   ├── README.md                    # Navigation guide
│   ├── VALIDATION.md                # ⭐ Input validation rules
│   ├── PARSER_TESTING.md            # ⭐ How to test parser
│   ├── 01-flowchart.md              # Control flow diagrams
│   ├── 02-swimlane.md               # Module responsibilities
│   ├── 03-sequence.md               # Component interactions
│   ├── 04-dataflow.md               # Data transformations
│   ├── 05-components.md             # File structure
│   └── 06-calltree.md               # Call hierarchy
│
├── geometry/                        # Geometry module
│   ├── README.md
│   ├── 01-components.md
│   ├── 02-cylinder-organization.md
│   ├── 03-sphere-to-world-calltree.md
│   ├── 04-typed-world-arrays.md
│   └── 06-plane-to-world-calltree.md
│
├── shapes-api.md                    # ⭐ Shapes creation API
├── QUICK_START.md                   # ⭐ Quick start guide
├── architecture-comparison.md       # Architecture options
├── memory-management.md             # Memory & debugging
├── rendering-optimization.md        # Performance tips
├── hybrid-architecture-flowchart.md
├── hybrid-heap-transition.md
├── heap-transition.md
├── include-hierarchy.md
└── matrix-determinant-flowchart.md
```

---

## ⭐ Essential Documentation (Start Here)

### 1. **Quick Start**
📄 `docs/QUICK_START.md`
- TL;DR guide for getting started
- Which architecture to use
- Common commands

### 2. **Parser Testing**
📄 `docs/parser/PARSER_TESTING.md`
- How to test parser with scene files
- Test scene formats
- Common issues and debugging

### 3. **Parser Validation**
📄 `docs/parser/VALIDATION.md`
- Input validation rules
- Value ranges (RGB, FOV, etc.)
- Error handling
- Why values are rejected (not clamped)

### 4. **Shapes API**
📄 `docs/shapes-api.md`
- How to create shapes (sphere, plane, cylinder)
- Transformation-based architecture
- Usage examples with flowcharts

---

## 🔧 Parser Module

### Architecture Documentation

**Navigation:** `docs/parser/README.md`

Six different views of parser architecture:
1. **Flowchart** - Control flow and conditionals
2. **Swimlane** - Module responsibilities
3. **Sequence** - Component interactions
4. **Data Flow** - Data transformations
5. **Components** - File structure
6. **Call Tree** - Function hierarchy

### Validation & Testing

**Input Validation:** `docs/parser/VALIDATION.md`
- RGB colors: [0-255] (rejected if out of range)
- FOV: [0-180 degrees]
- Ambient/brightness: [0.0-1.0]
- Normalized vectors required
- Format validation (no letters in numbers)

**Testing Guide:** `docs/parser/PARSER_TESTING.md`
```bash
# Test parser
./miniRT scenes/test_parser_all.rt

# Run automated tests
./test_parser.sh
```

---

## 🎨 Shapes & Objects

### Unified API

**Documentation:** `docs/shapes-api.md`

All shapes follow the same pattern:

```c
// Spheres
sphere_create() + sphere_set_transform() + sphere_set_material()

// Planes
plane_create() + plane_set_transform() + plane_set_material()

// Cylinders
cylinder_create() + cylinder_set_transform() + cylinder_set_material()
```

### Key Principle

✅ **Create unit primitives at origin**  
✅ **Transform to final position**  
✅ **Apply material properties**

This provides elegant, flexible architecture matching ray tracing math model.

---

## 📐 Geometry Module

**Location:** `docs/geometry/`

- Sphere, plane, cylinder, cone implementations
- Intersection algorithms
- Normal calculations
- World space transformations

---

## 🏗️ Architecture

### Options Comparison

**Documentation:** `docs/architecture-comparison.md`

Three approaches:
1. **Stack-based** (current) - Fast, limited capacity
2. **Heap-based** - Unlimited, slightly slower
3. **Hybrid** - Best of both worlds

### Memory Management

**Documentation:** `docs/memory-management.md`

- Stack trace diagrams for memory leaks
- Valgrind usage
- Cleanup best practices

---

## 🚀 Quick Commands

### Build & Run
```bash
make              # Compile project
./miniRT scene.rt # Run with scene file
```

### Testing
```bash
make run_test     # Run all 327 book tests
./test_parser.sh  # Test parser validation
```

### Validation
```bash
./check_norm.sh   # Check norminette
```

---

## ✅ Current Status

### Parser
- ✅ All elements supported (A, C, L, sp, pl, cy)
- ✅ Input validation (ranges, formats, normalization)
- ✅ Error handling (reject invalid input)
- ✅ 16/16 validation tests passing

### Objects
- ✅ Sphere implementation complete
- ✅ Plane implementation complete
- ✅ Cylinder implementation complete
- ✅ Unified transformation API

### Tests
- ✅ 327/327 book tests passing (100%)
- ✅ Chapters 1-13 validated
- ✅ All geometries tested

---

## 📝 Important Notes

### RGB Validation
**Values outside [0-255] are REJECTED, not clamped!**

This is correct per miniRT subject requirements.

Example:
```bash
# RGB = 256 → Error (not clamped to 255)
# RGB = 300 → Error (not clamped to 255)
# RGB = 255 → Valid
```

### Normalized Vectors
**Required for:**
- Camera orientation
- Plane normal
- Cylinder axis

Example:
```bash
# Valid (length = 1.0)
0,1,0

# Invalid (length ≠ 1.0)
0,0.5,1
```

---

## 🎯 Before Defense Checklist

- [ ] All 327 tests passing
- [ ] Parser handles valid scenes
- [ ] Parser rejects invalid scenes with Error
- [ ] RGB > 255 properly rejected
- [ ] All three object types render
- [ ] Norminette passes
- [ ] No memory leaks (valgrind)

---

## 📚 Additional Resources

### ASCII Diagram Style
All flowcharts use clean box-drawing characters:
```
┌─────────────────┐
│   Clean boxes   │
└────────┬────────┘
         │
         ▼
    Simple arrows
```

This style is consistent across all documentation.

### Scene File Format
```
A 0.2 255,255,255                    # Ambient
C 0,5,-10 0,0,1 70                   # Camera
L -5,10,0 0.7 255,255,255            # Light
sp 0,0,5 2 255,0,0                   # Sphere
pl 0,-1,0 0,1,0 100,100,100          # Plane
cy 3,0,5 0,1,0 1 4 0,255,0           # Cylinder
```

---

## 🔗 Quick Links

- **Start Here:** `docs/QUICK_START.md`
- **Parser Testing:** `docs/parser/PARSER_TESTING.md`
- **Validation Rules:** `docs/parser/VALIDATION.md`
- **Shapes API:** `docs/shapes-api.md`
- **Main README:** `README.md`

---

**Last Updated:** October 22, 2025  
**Status:** ✅ All systems operational
