# Rule to build libft before building tests
../libft/libft.a:
	@$(MAKE) -C ../libft

# Rule to build mlx before building tests (Linux)
../mlx-linux/libmlx_Linux.a:
	@$(MAKE) -s -C ../mlx-linux

# Rule to build mlx before building tests (macOS)
../minilibx-mms/libmlx.dylib:
	@$(MAKE) -s -C ../minilibx-mms
	@cp ../minilibx-mms/libmlx.dylib ../libmlx.dylib

# Makefile for The Raytracer Challenge Book Tests
# This Makefile builds and runs the organized test structure

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -O2
LDFLAGS = -L../libft -lft

# Directories
SRC_DIR = ../src
INCLUDE_DIR = ../include
TEST_DIR = .
CHAPTERS_DIR = chapters
OBJ_DIR = obj

# --- VALGRIND SUPPORT ---
# Usage: make test-ch5 V=1
RUNNER =
ifeq ($(V),1)
	VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=../mlx.supp
	RUNNER = valgrind $(VALGRIND_FLAGS)
endif

# Source files for the main project (excluding main.c to avoid conflicts)
SRCS = $(SRC_DIR)/window.c \
	$(SRC_DIR)/image.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/tuples/tuple_creation.c \
	$(SRC_DIR)/tuples/tuple_predicates.c \
	$(SRC_DIR)/tuples/tuple_utils.c \
	$(SRC_DIR)/tuples/tuple_multiply_divide.c \
	$(SRC_DIR)/tuples/tuple_magitude_normalize_dot.c \
	$(SRC_DIR)/tuples/tuple_reflect.c \
	$(SRC_DIR)/phisics/projectile.c \
	$(SRC_DIR)/tuples/colors.c \
	$(SRC_DIR)/tuples/color_converters.c \
	$(SRC_DIR)/tuples/pixel.c \
	$(SRC_DIR)/tuples/image_to_ppm.c \
	$(SRC_DIR)/matrices/matrices.c \
	$(SRC_DIR)/matrices/matrice_creation.c \
	$(SRC_DIR)/matrices/matrice_operations.c \
	$(SRC_DIR)/matrices/matrice_inverse.c \
	$(SRC_DIR)/matrices/matrice_submatrix.c \
	$(SRC_DIR)/matrices/transformations.c \
	$(SRC_DIR)/matrices/matrice_determinant_API.c \
	$(SRC_DIR)/matrices/matrice_determinant_recursive.c \
	$(SRC_DIR)/rays/rays.c \
	$(SRC_DIR)/spheres/spheres.c \
	$(SRC_DIR)/spheres/sphere_normal.c \
	$(SRC_DIR)/spheres/sphere_render_grid.c \
	$(SRC_DIR)/spheres/sphere_render_phong.c \
	$(SRC_DIR)/spheres/sphere_intersect.c \
	$(SRC_DIR)/spheres/sphere_render.c \
	$(SRC_DIR)/intersections/intersections.c \
	$(SRC_DIR)/intersections/utils.c \
	$(SRC_DIR)/math/math_utils.c \
	$(SRC_DIR)/matrices/matrice_rotation.c \
	$(SRC_DIR)/materials/materials.c \
	$(SRC_DIR)/materials/lighting.c \
	$(SRC_DIR)/lights/lights.c \
	$(SRC_DIR)/world/world.c \
	$(SRC_DIR)/computations/computations.c \
	$(SRC_DIR)/camera/camera.c \
	$(SRC_DIR)/render/render.c

# Test source files
TEST_SRCS = test_common.c \
	test_runner.c \
	$(CHAPTERS_DIR)/test_chapter1.c \
	$(CHAPTERS_DIR)/test_chapter2.c \
	$(CHAPTERS_DIR)/test_chapter3.c \
	$(CHAPTERS_DIR)/test_chapter4.c \
	$(CHAPTERS_DIR)/test_chapter5.c \
	$(CHAPTERS_DIR)/test_chapter6.c \
	$(CHAPTERS_DIR)/test_chapter7.c \
	$(CHAPTERS_DIR)/test_chapter8.c \

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:%.c=$(OBJ_DIR)/%.o)

# Target executable
TARGET = run_test

# MLX library paths (detect OS)
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLX_DIR = ../mlx-linux
	MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
	MLX_INCLUDE = -I$(MLX_DIR)
else
	MLX_DIR = ../minilibx-mms
	MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
	MLX_INCLUDE = -I$(MLX_DIR)
endif

# Include directories
INCLUDES = -I$(INCLUDE_DIR) -I$(MLX_DIR) -I../libft/inc $(MLX_INCLUDE)

# Default target
all: $(TARGET)

# Build main project object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build test object files
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


# Link the test executable (with OS-specific MLX dependencies)
ifeq ($(UNAME_S),Linux)
$(TARGET): $(OBJS) $(TEST_OBJS) ../libft/libft.a ../mlx-linux/libmlx_Linux.a
	$(CC) $(OBJS) $(TEST_OBJS) -o $@ $(LDFLAGS) $(MLX_FLAGS) -lm
else
$(TARGET): $(OBJS) $(TEST_OBJS) ../libft/libft.a ../minilibx-mms/libmlx.dylib
	$(CC) $(OBJS) $(TEST_OBJS) -o $@ $(LDFLAGS) $(MLX_FLAGS) -lm
	@cp ../minilibx-mms/libmlx.dylib ./libmlx.dylib
endif

# Run all tests
test: $(TARGET)
	./$(TARGET)

# Run tests with valgrind (if available)
vtest: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Clean up
clean:
	rm -rf $(OBJ_DIR)
	rm -f libmlx.dylib
	rm -f *.ppm
	rm -rf ../demos/output/*.ppm

fclean: clean
	rm -f $(TARGET)
	rm -f ../libmlx.dylib

re: fclean all

# Individual chapter tests (for debugging)
test-ch1: $(TARGET)
	$(RUNNER) ./$(TARGET) 1

test-ch2: $(TARGET)
	$(RUNNER) ./$(TARGET) 2

test-ch3: $(TARGET)
	$(RUNNER) ./$(TARGET) 3

test-ch4: $(TARGET)
	$(RUNNER) ./$(TARGET) 4

test-ch5: $(TARGET)
	$(RUNNER) ./$(TARGET) 5

test-ch6: $(TARGET)
	$(RUNNER) ./$(TARGET) 6

test-ch7: $(TARGET)
	$(RUNNER) ./$(TARGET) 7

test-ch8: $(TARGET)
	$(RUNNER) ./$(TARGET) 8

# Run all tests with Valgrind (Linux only)
test-all-valgrind: $(TARGET)
	@echo "🔍 Running ALL tests with Valgrind..."
	@echo "=========================================="
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind_all.log ./$(TARGET)
	@echo "=========================================="
	@echo "✅ All tests with Valgrind completed!"
	@echo "📋 Check valgrind_all.log for details"

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Build the organized test suite"
	@echo "  test             - Run all tests"
	@echo "  vtest            - Run tests with valgrind"
	@echo "  test-all-valgrind - Run ALL tests with Valgrind (Linux only)"
	@echo "  clean            - Remove object files"
	@echo "  fclean           - Remove object files and executable"
	@echo "  re               - Rebuild everything"
	@echo "  test-ch1         - Run only Chapter 1 tests"
	@echo "  test-ch2         - Run only Chapter 2 tests"
	@echo "  test-ch3         - Run only Chapter 3 tests"
	@echo "  test-ch4         - Run only Chapter 4 tests"
	@echo "  test-ch5         - Run only Chapter 5 tests"
	@echo "  test-ch6         - Run only Chapter 6 tests"
	@echo "  test-ch7         - Run only Chapter 7 tests"
	@echo "  test-ch8         - Run only Chapter 8 tests"
	@echo "  help             - Show this help message"

.PHONY: all test vtest test-all-valgrind clean fclean re test-ch1 test-ch2 test-ch3 test-ch4 test-ch5 test-ch6 test-ch7 test-ch8 help
