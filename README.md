# How to Run miniRT Program

## Initial Setup
```bash
# Download submodule with miniLibX (mlx)
git submodule update --init --recursive
```
## Building and Running the Main Program
```bash
# Build the main miniRT project
make
# or
make re

# Run the program
./miniRT
# Starts a window that can be closed with the X button or ESC key
```
# Quick render with make (automatically builds if needed)
make run SCENE=scenes/3_spheres.rt

# or with verbose build output (this is light scene to test fast also use smaller window)
make run SCENE=scenes/3_spheres.rt V=1


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
