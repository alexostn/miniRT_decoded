# The Raytracer Challenge Book Tests - Organized Structure

This directory contains a reorganized version of all tests from "The Raytracer Challenge" book, separated by chapters for easier maintenance and debugging.

## 🧪 Parser Tests

### Quick Start

```bash
# Run parser integration tests (tests full scene parsing)
make test-parser

# Run parser unit tests (tests individual parsing functions)
make test-parse-unit
```

### Parser Test Files

- **test_parser_simple.c** - Integration tests for complete scene file parsing
- **test_parse.c** - Unit tests for individual parsing functions (parse_double, parse_vector3, etc.)

## 🚀 How to Use the Test System

### Option 1: From the main project directory

```bash
# Run all organized tests from Mac
make -f Makefile_mac run_test

# Run all organized tests from ubuntu
make run_test

# Run parser tests
make test-parser          # Integration tests
make test-parse-unit      # Unit tests

# Run tests for a specific chapter on Mac
make -f Makefile_mac test-ch1    # Chapter 1: Tuples
make -f Makefile_mac test-ch2    # Chapter 2: Colors
make -f Makefile_mac test-ch3    # Chapter 3: Matrices
make -f Makefile_mac test-ch4    # Chapter 4: Transformations
make -f Makefile_mac test-ch5    # Chapter 5: Ray-Sphere Intersections
```
# Run tests for a specific chapter on ubuntu

make test-ch1    # Chapter 1: Tuples
make test-ch2    # Chapter 2: Colors
make test-ch3    # Chapter 3: Matrices
make test-ch4    # Chapter 4: Transformations
make test-ch5    # Chapter 5: Ray-Sphere Intersections
make test-ch1    # Chapter 1: Tuples
make test-ch2    # Chapter 2: Colors
make test-ch3    # Chapter 3: Matrices
make test-ch4    # Chapter 4: Transformations
make test-ch5    # Chapter 5: Ray-Sphere Intersections
make test-ch6    # Chapter 6: Light and Shading
make test-ch7    # Chapter 7: Making a Scene

# Run tests for a specific chapter on ubuntu with Valgrind
make test-ch1 V=1   # Chapter 1: Tuples
make test-ch2 V=1   # Chapter 2: Colors
make test-ch3 V=1   # Chapter 3: Matrices
make test-ch4 V=1   # Chapter 4: Transformations
make test-ch5 V=1   # Chapter 5: Ray-Sphere Intersections
make test-ch1 V=1   # Chapter 1: Tuples
make test-ch2 V=1   # Chapter 2: Colors
make test-ch3 V=1   # Chapter 3: Matrices
make test-ch4 V=1   # Chapter 4: Transformations
make test-ch5 V=1   # Chapter 5: Ray-Sphere Intersections
make test-ch6 V=1   # Chapter 6: Light and Shading
make test-ch7 V=1   # Chapter 7: Making a Scene
```

### Option 2: From the tests directory

```bash
cd tests/

# Run all tests
make run_test

# Run tests with valgrind (works only from tests/)
make vtest

# Run tests for a specific chapter
make test-ch1
make test-ch2
make test-ch3
make test-ch4
make test-ch5

# View help
make help
```

## 🏗️ File Structure Details

### Core Test Files

#### `test_common.h` & `test_common.c`
- **Purpose**: Shared utilities and common functions
- **Contains**: 
  - Common includes (`tuples.h`, `matrices.h`, `rays.h`, etc.)
  - Utility functions (`print_ray`, `print_intersections`, `compare_files`)
  - Test assertion macro (`TEST_ASSERT`)

#### `test_runner.c`
- **Purpose**: Main executable that orchestrates all tests
- **Contains**:
  - `main()` function
  - Calls to `run_chapterX_tests()` for each chapter
  - Global test statistics and reporting

#### `chapters/test_chapterX.c`
- **Purpose**: Contains all tests for a specific chapter
- **Structure**:
  - Individual test functions (e.g., `test_ch1_tuple_is_point()`)
  - Chapter runner function (e.g., `run_chapter1_tests()`)
  - All tests from the original `book_tests.c` file

## 📝 How to Create a New Test File

### Step 1: Create the Test File

Create a new file `chapters/test_chapterX.c` with this structure:

```c
#include "../test_common.h"

// Chapter X: [Chapter Name] - Complete with all Y tests

void test_chX_example_function(void)
{
    printf("Chapter X: Description of what this test does\n");
    
    // Arrange: Set up test data
    t_tuple example = point(1, 2, 3);
    
    // Act: Perform the operation being tested
    t_tuple result = some_function(example);
    
    // Assert: Check the results
    TEST_ASSERT(tuples_equal(result, expected), "Description of expected result");
    printf("\n");
}

// Add more test functions here...

// Main function to run all Chapter X tests
void run_chapterX_tests(void)
{
    printf("\n=== Chapter X: [Chapter Name] ===\n");
    
    test_chX_example_function();
    // Add calls to other test functions here...
    
    printf("\n=== Chapter X Tests Complete ===\n\n");
}
```

### Step 2: Update the Test Runner

Add your new chapter to `test_runner.c`:

```c
// In the main() function, add:
run_chapterX_tests();
```

### Step 3: Update the Makefile

Add your new test file to `tests/Makefile`:

```makefile
TEST_SRCS = test_common.c \
    test_runner.c \
    $(CHAPTERS_DIR)/test_chapter1.c \
    $(CHAPTERS_DIR)/test_chapter2.c \
    $(CHAPTERS_DIR)/test_chapter3.c \
    $(CHAPTERS_DIR)/test_chapter4.c \
    $(CHAPTERS_DIR)/test_chapter5.c \
    $(CHAPTERS_DIR)/test_chapterX.c  # Add this line
```

### Step 4: Add Individual Chapter Target (Optional)

Add a new target to `tests/Makefile`:

```makefile
test-chX: $(TARGET)
    $(RUNNER) ./$(TARGET) | grep -A 1000 "Chapter X:"
# RUNNER enables Valgrind option
# f.ex.: 'make V=1 test-ch1'
```

And update the main Makefiles (`Makefile` and `Makefile_mac`):

```makefile
test-chX:
    cd tests && make test-chX
```

## 🔧 Compilation Instructions

### Compile Tests Separately

```bash
# From the tests directory
cd tests/

# Compile only the test system
make

# Clean and recompile
make clean && make

# Force clean everything
make fclean && make
```

### Compile Tests Together with Main Project

```bash
# From the main project directory

# Compile main project
make -f Makefile_mac

# Compile and run tests (automatically compiles tests if needed)
make -f Makefile_mac run_test

# Compile specific chapter tests
make -f Makefile_mac test-ch1
```

### Manual Compilation (Advanced)

If you need to compile manually:

```bash
cd tests/

# Compile test objects
gcc -Wall -Wextra -Werror -g -O2 -I../include -I../minilibx-mms -I../libft/inc \
    -c test_common.c -o obj/test_common.o
gcc -Wall -Wextra -Werror -g -O2 -I../include -I../minilibx-mms -I../libft/inc \
    -c test_runner.c -o obj/test_runner.o
gcc -Wall -Wextra -Werror -g -O2 -I../include -I../minilibx-mms -I../libft/inc \
    -c chapters/test_chapter1.c -o obj/chapters/test_chapter1.o

# Link everything together
gcc obj/test_common.o obj/test_runner.o obj/chapters/test_chapter1.o \
    [other object files...] -o run_test \
    -L../libft -lft -L../minilibx-mms -lmlx -framework OpenGL -framework AppKit -lm
```

## 📊 Test Statistics

The system maintains global statistics:
- **Total tests executed**: 178 tests
- **Tests passed/failed**: 178/0 ✅
- **Success rate**: 100.0% 🎯
- **Failed tests list**: None

### 📊 Distribution by Chapter:
- **Chapter 1**: 27 tests (Tuples, Points, Vectors)
- **Chapter 2**: 12 tests (Colors and Canvas)  
- **Chapter 3**: 12 tests (Matrices)
- **Chapter 4**: 3 tests (Transformations)
- **Chapter 5**: 20 tests (Ray-Sphere Intersections)

## 🔧 Available Commands

| Command | Description |
|---------|-------------|
| `make run_test` | Run all tests |
| `make test` | Run all tests (alias) |
| `make vtest` | Run tests with valgrind |
| `make test-ch1` | Only Chapter 1 tests |
| `make test-ch2` | Only Chapter 2 tests |
| `make test-ch3` | Only Chapter 3 tests |
| `make test-ch4` | Only Chapter 4 tests |
| `make test-ch5` | Only Chapter 5 tests |
| `make clean` | Clean object files |
| `make fclean` | Clean everything |
| `make help` | Show complete help |

## 🛠️ Development and Maintenance

### Adding a New Test

1. Open the corresponding chapter file (e.g., `chapters/test_chapter1.c`)
2. Add your test function following the existing pattern
3. Call your function from `run_chapterX_tests()`

### Modifying an Existing Test

1. Locate the test in the corresponding chapter file
2. Make your modifications
3. Run only that chapter to verify: `make test-chX`

### Adding a New Chapter

1. Create `chapters/test_chapterX.c` following the structure above
2. Implement `run_chapterX_tests()`
3. Add the call in `test_runner.c`
4. Update the Makefiles as shown above
