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

## Testing System (NEW UNIFIED SYSTEM)

### Run All Tests
```bash
# Run ALL chapter tests with consolidated summary
make test-all
# Shows: Chapter 1-5 results + TOTAL: 200/200 tests ✅ (100.0%)
```

### Run Individual Chapter Tests #works and shows more then one mistake, just some strange Makefile errors at the end, but this probably not that important
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
# Outputs to: tests/valgrind_all.log #works
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
***find . -type d -iname "files"***
***find . -type f -name "*.ppm" ***
- Test results show detailed output for each chapter
- Memory leak reports saved to `tests/valgrind_all.log` (Linux)

## Notes
- The unified Makefile works on both Mac and Linux
- All 200 tests should pass (100% success rate)
- PPM files are automatically generated and compared during tests
