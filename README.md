
[📚 Documentation Overview](docs/README_EXPLAIN.md)


# How to Run miniRT Program

## Initial Setup

# Download submodule with miniLibX (mlx)
```
git submodule update --init --recursive
```

## Building and Running the Main Program

### Build Modes

- **Mandatory:**  
	Build the standard version (single light, no cones):
	```
	make
	```
	# or
	```
	make all
	```

- **Bonus:**  
	Build the bonus version (multiple lights, cones, extra features):
	```
	make bonus
	```

# How to Run miniRT Program
./miniRT scenes/valid_scenes/3_spheres.rt
# Starts a window that can be closed with the X button or ESC key

## VIEWING RENDERED IMAGES IN A SEPARATE WINDOW

# To open
# rendered image in a separate viewer window
# (useful for comparing results while rendering from a terminal), run in another terminal:

```
eog output/render_1.ppm
```

# This will open `output/render_1.ppm` with EOG (Eye of GNOME). Note that EOG does not always automatically refresh when the file is overwritten by the renderer — you may need to manually reload the image (View → Reload) or close and re-open the file to see the updated image.

# Before re-rendering you may want to clean the `output` folder so only fresh images are present:

```
make fclean
```

# If you prefer an auto-reloading viewer, consider using `feh` which can periodically reload the file:

```
feh --reload 1 output/render_1.ppm
```

# The `--reload 1` option refreshes the image every second. Arrange your windows (for example, place the viewer in the top-right corner and your terminal/editor next to it) to visually compare changes between renders.

---
# VALGRIND CHECKING TIPS:
# First of all resize window include/defines.h
```
/*...small resolution for fast rendering (2.5x subject)*/
# define WIN_WIDTH 20
# define WIN_HEIGHT 10
```

# Valgrind memory checking 'V=1' flag (Linux only):
make run SCENE=scenes/valid_scenes/3_spheres.rt V=1
# (V=1 works only with 'make run', not with direct ./miniRT execution)
#
# Note:
# - 'make run SCENE=...' launches the version of miniRT (mandatory or bonus) that was built last.
# - 'make bonus run SCENE=...' will build and immediately run the bonus version, regardless of previous builds.
# - 'make run SCENE=...' after 'make' runs the mandatory version; after 'make bonus' runs the bonus version.

---

## Testing System (NEW UNIFIED SYSTEM) not at eval repo

### Run All Tests
```bash
# Run ALL chapter tests with consolidated summary
make test-all
# Shows: Chapter 1-5 results + TOTAL: 200/200 tests ✅ (100.0%)
```

### Run Individual Chapter Tests
```bash
make test-ch1    # Chapter 1: Tuples, Points, and Vectors (50 tests)
make test-ch2    # Chapter 2: Colors and Canvas (32 tests)
make test-ch3    # Chapter 3: Matrices (48 tests)
make test-ch4    # Chapter 4: Transformations (25 tests)
make test-ch5    # Chapter 5: Ray-Sphere Intersections (45 tests)
```

### Memory Testing (Linux only)
```bash
# Run all tests with Valgrind memory checking
make test-all-valgrind
# Outputs to: tests/valgrind_all.log
```

### Help and Available Commands
```bash
# Show all available make commands
make help
```

## Cross-Platform Support
The Makefile automatically detects your OS:
- **Linux**: Uses `mlx-linux` with X11 libraries
- **macOS**: Uses `minilibx-mms` with Cocoa/OpenGL frameworks

## Cleaning Up
```bash
# Remove object files and executables
make fclean
# Also removes valgrind.log files
```

## Code Style Checking
# Run norminette on the project
```
./check_norm.sh
```
# (Includes automatic .normignore handling)

## Test Output Files
- PPM files are generated in `tests/files/` directory
- Test results show detailed output for each chapter
- Memory leak reports saved to `tests/valgrind_all.log` (Linux)

## Notes
- The unified Makefile works on both Mac and Linux
- All 200 tests should pass (100% success rate)
- PPM files are automatically generated and compared during tests

## Documentation
🎯 **[Entry for Parser Architecture Documentation](docs/parser/06-calltree.md)**
📚 **[Parser Architecture Documentation](docs/parser/)** — comprehensive diagrams and guides for understanding the parser module (flowcharts, data flow, call trees, etc.)

� **[Geometry Module Documentation](docs/geometry/)** — structure of geometric objects (spheres, planes, cylinders, cones), intersection algorithms, normal calculations

�🔧 **[Memory Management & Debugging](docs/memory-management.md)** — stack trace diagrams for common memory leaks, Valgrind usage, and cleanup best practices

🚀 **Architecture Transition Plans:**
- **⚡ [Quick Start Guide](docs/QUICK_START.md)** — TL;DR: Which architecture to use? Start here!
- **[Architecture Comparison](docs/architecture-comparison.md)** — detailed benchmark: stack vs heap vs hybrid (⚙️ **recommended read**)
- **[Hybrid Heap Transition](docs/hybrid-heap-transition.md)** — stack for small scenes, heap for overflow (configurable `HEAP_THRESHOLD`)
- **[Hybrid Architecture Flowchart](docs/hybrid-architecture-flowchart.md)** — visual diagrams for hybrid approach
- **[Full Heap Migration](docs/heap-transition.md)** — complete replacement with dynamic allocation from start

### Rendering Optimization (short)

The renderer currently spends most time in geometry traversal (per-pixel world intersection and shadow checks). See `docs/rendering-optimization.md` for the full guide. Key ideas:

- Cache and reuse the primary hit during shading to avoid duplicate traversals.
- Provide `world_intersect()` and `world_occluded()` wrappers that use an acceleration structure when available.
- Build a BVH (median-split, optionally SAH) to avoid O(N) per-ray sphere tests.
- Use early-out occlusion checks for shadow rays and parallelize rendering by tiles.

Full implementation notes, microbenchmarks and an incremental plan are available in the document:

📄 [Rendering Optimization — full guide](docs/rendering-optimization.md)

## Testing System (NEW UNIFIED SYSTEM)

### Run All Tests
```bash
# Run ALL chapter tests with consolidated summary
make test-all
# Shows: Chapter 1-5 results + TOTAL: 200/200 tests ✅ (100.0%)
```

### Run Individual Chapter Tests
```bash
make test-ch1    # Chapter 1: Tuples, Points, and Vectors (50 tests)
make test-ch2    # Chapter 2: Colors and Canvas (32 tests)
make test-ch3    # Chapter 3: Matrices (48 tests)
make test-ch4    # Chapter 4: Transformations (25 tests)
make test-ch5    # Chapter 5: Ray-Sphere Intersections (45 tests)
```

### Memory Testing (Linux only)
```bash
# Run all tests with Valgrind memory checking
make test-all-valgrind
# Outputs to: tests/valgrind_all.log
```

### Help and Available Commands
```bash
# Show all available make commands
make help
```

## Cross-Platform Support
The Makefile automatically detects your OS:
- **Linux**: Uses `mlx-linux` with X11 libraries
- **macOS**: Uses `minilibx-mms` with Cocoa/OpenGL frameworks

## Cleaning Up
```bash
# Remove object files and executables
make fclean
# Also removes valgrind.log files
```

## Code Style Checking
```bash
# Run norminette on the project
./check_norm.sh
# (Includes automatic .normignore handling)
```

## Test Output Files
- PPM files are generated in `tests/files/` directory
- Test results show detailed output for each chapter
- Memory leak reports saved to `tests/valgrind_all.log` (Linux)

## Notes
- The unified Makefile works on both Mac and Linux
- All 200 tests should pass (100% success rate)
- PPM files are automatically generated and compared during tests



## Documentation
🎯 **[Entry for Parser Architecture Documentation](docs/parser/06-calltree.md)**
📚 **[Parser Architecture Documentation](docs/parser/)** — comprehensive diagrams and guides for understanding the parser module (flowcharts, data flow, call trees, etc.)

� **[Geometry Module Documentation](docs/geometry/)** — structure of geometric objects (spheres, planes, cylinders, cones), intersection algorithms, normal calculations

�🔧 **[Memory Management & Debugging](docs/memory-management.md)** — stack trace diagrams for common memory leaks, Valgrind usage, and cleanup best practices

🚀 **Architecture Transition Plans:**
- **⚡ [Quick Start Guide](docs/QUICK_START.md)** — TL;DR: Which architecture to use? Start here!
- **[Architecture Comparison](docs/architecture-comparison.md)** — detailed benchmark: stack vs heap vs hybrid (⚙️ **recommended read**)
- **[Hybrid Heap Transition](docs/hybrid-heap-transition.md)** — stack for small scenes, heap for overflow (configurable `HEAP_THRESHOLD`)
- **[Hybrid Architecture Flowchart](docs/hybrid-architecture-flowchart.md)** — visual diagrams for hybrid approach
- **[Full Heap Migration](docs/heap-transition.md)** — complete replacement with dynamic allocation from start

### Rendering Optimization (short)

The renderer currently spends most time in geometry traversal (per-pixel world intersection and shadow checks). See `docs/rendering-optimization.md` for the full guide. Key ideas:

- Cache and reuse the primary hit during shading to avoid duplicate traversals.
- Provide `world_intersect()` and `world_occluded()` wrappers that use an acceleration structure when available.
- Build a BVH (median-split, optionally SAH) to avoid O(N) per-ray sphere tests.
- Use early-out occlusion checks for shadow rays and parallelize rendering by tiles.

Full implementation notes, microbenchmarks and an incremental plan are available in the document:

📄 [Rendering Optimization — full guide](docs/rendering-optimization.md)
