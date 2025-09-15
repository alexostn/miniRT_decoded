# Rule to build libft before building tests
../libft/libft.a:
	@$(MAKE) -C ../libft

# Rule to build mlx before building tests
../mlx-linux/libmlx_Linux.a:
	@$(MAKE) -s -C ../mlx-linux

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

# Source files for the main project (excluding main.c to avoid conflicts)
SRCS = $(SRC_DIR)/window.c \
	$(SRC_DIR)/image.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/tuples/tuple_creation.c \
	$(SRC_DIR)/tuples/tuple_predicates.c \
	$(SRC_DIR)/tuples/tuple_utils.c \
	$(SRC_DIR)/tuples/tuple_multiply_divide.c \
	$(SRC_DIR)/tuples/tuple_magitude_normalize_dot.c \
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
	$(SRC_DIR)/spheres/intersections_utils.c

# Test source files
TEST_SRCS = test_common.c \
	test_runner.c \
	$(CHAPTERS_DIR)/test_chapter1.c \
	$(CHAPTERS_DIR)/test_chapter2.c \
	$(CHAPTERS_DIR)/test_chapter3.c \
	$(CHAPTERS_DIR)/test_chapter4.c \
	$(CHAPTERS_DIR)/test_chapter5.c

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

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/tuples
	mkdir -p $(OBJ_DIR)/matrices
	mkdir -p $(OBJ_DIR)/phisics
	mkdir -p $(OBJ_DIR)/rays
	mkdir -p $(OBJ_DIR)/spheres
	mkdir -p $(OBJ_DIR)/chapters

# Build main project object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build test object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link the test executable
$(TARGET): $(OBJS) $(TEST_OBJS) ../libft/libft.a ../mlx-linux/libmlx_Linux.a
	$(CC) $(OBJS) $(TEST_OBJS) -o $@ $(LDFLAGS) $(MLX_FLAGS) -lm

# Run all tests
test: $(TARGET)
	./$(TARGET)

# Run tests with valgrind (if available)
vtest: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

# Clean up
clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

# Individual chapter tests (for debugging)
test-ch1: $(TARGET)
	./$(TARGET) | grep -A 1000 "Chapter 1:"

test-ch2: $(TARGET)
	./$(TARGET) | grep -A 1000 "Chapter 2:"

test-ch3: $(TARGET)
	./$(TARGET) | grep -A 1000 "Chapter 3:"

test-ch4: $(TARGET)
	./$(TARGET) | grep -A 1000 "Chapter 4:"

test-ch5: $(TARGET)
	./$(TARGET) | grep -A 1000 "Chapter 5:"

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the organized test suite"
	@echo "  test     - Run all tests"
	@echo "  vtest    - Run tests with valgrind"
	@echo "  clean    - Remove object files"
	@echo "  fclean   - Remove object files and executable"
	@echo "  re       - Rebuild everything"
	@echo "  test-ch1 - Run only Chapter 1 tests"
	@echo "  test-ch2 - Run only Chapter 2 tests"
	@echo "  test-ch3 - Run only Chapter 3 tests"
	@echo "  test-ch4 - Run only Chapter 4 tests"
	@echo "  test-ch5 - Run only Chapter 5 tests"
	@echo "  help     - Show this help message"

.PHONY: all test vtest clean fclean re test-ch1 test-ch2 test-ch3 test-ch4 test-ch5 help
