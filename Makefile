# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 17:57:48 by oostapen          #+#    #+#              #
#    Updated: 2025/10/02 22:25:49 by oostapen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for miniRT (C, miniLibX, cross-platform)
NAME    = miniRT
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -Iinclude -Itests/ -I$(LIBFT_DIR) -I$(LIBFT_DIR)/inc -I$(MLX_DIR)

# OS Detection
UNAME_S := $(shell uname -s)

# Libft variables:
LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# MiniLibX variables (OS-specific):
ifeq ($(UNAME_S),Linux)
	MLX_DIR = mlx-linux
	MLX_LIB = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
	MLX_TARGET = $(MLX_DIR)/libmlx.a
	MLX_CLEAN_TARGET = $(MLX_DIR)/libmlx.a
else
	MLX_DIR = minilibx-mms
	MLX_LIB = -L. -lmlx -framework Cocoa -framework OpenGL -framework IOKit
	MLX_TARGET = libmlx.dylib
	MLX_CLEAN_TARGET = libmlx.dylib
endif

# --- VALGRIND (OPTIONAL RUNNER) ---
# Usage: make <target> V=1
RUNNER =
ifeq ($(V),1)
	VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=mlx.supp
	RUNNER = valgrind $(VALGRIND_FLAGS)
endif

# Project variables:
SRC_DIR = src
OBJ_DIR = obj

SRCS	= $(SRC_DIR)/main.c \
			$(SRC_DIR)/window.c \
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
			$(SRC_DIR)/rays/rays.c \
			$(SRC_DIR)/spheres/spheres.c \
			$(SRC_DIR)/spheres/sphere_normal.c \
			$(SRC_DIR)/spheres/sphere_render_grid.c \
			$(SRC_DIR)/spheres/sphere_render_phong.c \
			$(SRC_DIR)/spheres/sphere_intersect.c \
			$(SRC_DIR)/intersections/intersections.c \
			$(SRC_DIR)/intersections/utils.c \
			$(SRC_DIR)/materials/materials.c \
			$(SRC_DIR)/materials/lighting.c \
			$(SRC_DIR)/lights/lights.c \
			$(SRC_DIR)/matrices/matrice_submatrix.c \
			$(SRC_DIR)/matrices/transformations.c \
			$(SRC_DIR)/matrices/matrice_determinant_API.c \
			$(SRC_DIR)/matrices/matrice_determinant_recursive.c \
			$(SRC_DIR)/math/math_utils.c \
			$(SRC_DIR)/matrices/matrice_rotation.c \
			$(SRC_DIR)/spheres/spheres_intersect_stack.c \
			$(SRC_DIR)/spheres/intersects_collection_stack.c \
			$(SRC_DIR)/world/world.c \
			$(SRC_DIR)/computations/computations.c


OBJS	= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Variables for booktests (REMOVED - no longer used)

# >>> MODULE TESTING SECTION (REMOVED - no longer used)

# Default target
.DEFAULT_GOAL := all

# basic rules:
all: $(NAME)

# Dependencies for the main project
$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_TARGET)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAGS) $(MLX_LIB) -o $(NAME)
	@echo "✅ miniRT compiled successfully!"

# libft compilation rule:
$(LIBFT_LIB):
	@echo "📚 Compiling libft..."
	@make -s -C $(LIBFT_DIR)
	@echo "✅ libft compiled successfully!"

# MLX compilation rules (OS-specific):
ifeq ($(UNAME_S),Linux)
# Linux MLX compilation rule:
$(MLX_DIR)/Makefile.gen:
	cd $(MLX_DIR) && ./configure

$(MLX_TARGET): $(MLX_DIR)/Makefile.gen
	@echo "🖼️  Compiling mlx-linux..."
	@make -s -C $(MLX_DIR)
	@echo "✅ mlx-linux compiled successfully!"
else
# macOS MLX compilation rule:
$(MLX_TARGET):
	@echo "🖼️  Compiling minilibx-mms..."
	@make -s -C $(MLX_DIR)
	@cp $(MLX_DIR)/libmlx.dylib .
	@echo "✅ libmlx.dylib copied to project root"
endif

# Rule for compiling .c from src/ to obj/ (for the main project and test modules)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# --- DEMOS ---
CLOCK_SRC       = demos/clock_main.c
CLOCK_EXEC      = clock_demo
CLOCK_OBJS      = $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

SPHERE_SRC      = demos/sphere_render_main.c
SPHERE_EXEC     = sphere_demo
SPHERE_OBJS     = $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) $(OBJ_DIR)/spheres/sphere_render.o
# --- END OF DEMOS ---
	
# clean rules:
clean:
	@make -s -C $(LIBFT_DIR) clean
	@make -s -C $(MLX_DIR) clean
	rm -f $(OBJS)
	rm -rf $(OBJ_DIR)
	@echo "🧹 Cleaning output files..."
	rm -rf demos/output
	rm -rf tests/files/output

fclean: clean
	@make -s -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f valgrind.log
	rm -f $(MLX_CLEAN_TARGET)
	rm -rf $(CLOCK_EXEC)
	rm -rf $(SPHERE_EXEC)
	rm -rf demos/output

re: fclean all

# New organized test system
run_test:
	cd tests && make test

test-ch1:
	cd tests && make test-ch1

test-ch2:
	cd tests && make test-ch2

test-ch3:
	cd tests && make test-ch3

test-ch4:
	cd tests && make test-ch4

test-ch5:
	cd tests && make test-ch5

test-ch6:
	cd tests && make test-ch6
	
test-ch7:
	cd tests && make test-ch7

# Run all chapter tests
test-all:
	@echo "🚀 Running ALL chapter tests..."
	@echo "=========================================="
	@ch1_result=0; ch2_result=0; ch3_result=0; ch4_result=0; ch5_result=0; ch6_result=0; ch7_result=0; \
	echo "Running Chapter 1 tests..."; \
	$(MAKE) test-ch1 > /dev/null 2>&1; ch1_result=$$?; \
	if [ $$ch1_result -eq 0 ]; then \
		echo "Chapter 1: ✅ PASSED"; \
	else \
		echo "Chapter 1: ❌ FAILED"; \
	fi; \
	echo ""; \
	echo "Running Chapter 2 tests..."; \
	$(MAKE) test-ch2 > /dev/null 2>&1; ch2_result=$$?; \
	if [ $$ch2_result -eq 0 ]; then \
		echo "Chapter 2: ✅ PASSED"; \
	else \
		echo "Chapter 2: ❌ FAILED"; \
	fi; \
	echo ""; \
	echo "Running Chapter 3 tests..."; \
	$(MAKE) test-ch3 > /dev/null 2>&1; ch3_result=$$?; \
	if [ $$ch3_result -eq 0 ]; then \
		echo "Chapter 3: ✅ PASSED"; \
	else \
		echo "Chapter 3: ❌ FAILED"; \
	fi; \
	echo ""; \
	echo "Running Chapter 4 tests..."; \
	$(MAKE) test-ch4 > /dev/null 2>&1; ch4_result=$$?; \
	if [ $$ch4_result -eq 0 ]; then \
		echo "Chapter 4: ✅ PASSED"; \
	else \
		echo "Chapter 4: ❌ FAILED"; \
	fi; \
	echo ""; \
	echo "Running Chapter 5 tests..."; \
	$(MAKE) test-ch5 > /dev/null 2>&1; ch5_result=$$?; \
	if [ $$ch5_result -eq 0 ]; then \
		echo "Chapter 5: ✅ PASSED"; \
	else \
		echo "Chapter 5: ❌ FAILED"; \
	fi; \
	echo ""; \
	echo "Running Chapter 6 tests..."; \
	$(MAKE) test-ch6 > /dev/null 2>&1; ch6_result=$$?; \
	if [ $$ch6_result -eq 0 ]; then \
		echo "Chapter 6: ✅ PASSED"; \
	else \
		echo "Chapter 6: ❌ FAILED"; \
	fi; \
	echo ""; \
	echo "Running Chapter 7 tests..."; \
	$(MAKE) test-ch7 > /dev/null 2>&1; ch7_result=$$?; \
	if [ $$ch7_result -eq 0 ]; then \
		echo "Chapter 7: ✅ PASSED"; \
	else \
		echo "Chapter 7: ❌ FAILED"; \
	fi; \
	echo ""; \
	echo "=========================================="; \
	echo "📊 FINAL SUMMARY - ALL CHAPTERS"; \
	echo "=========================================="; \
	total_failed=0; \
	if [ $$ch1_result -ne 0 ]; then total_failed=$$((total_failed + 1)); fi; \
	if [ $$ch2_result -ne 0 ]; then total_failed=$$((total_failed + 1)); fi; \
	if [ $$ch3_result -ne 0 ]; then total_failed=$$((total_failed + 1)); fi; \
	if [ $$ch4_result -ne 0 ]; then total_failed=$$((total_failed + 1)); fi; \
	if [ $$ch5_result -ne 0 ]; then total_failed=$$((total_failed + 1)); fi; \
	if [ $$ch6_result -ne 0 ]; then total_failed=$$((total_failed + 1)); fi; \
	if [ $$ch7_result -ne 0 ]; then total_failed=$$((total_failed + 1)); fi; \
	passed=$$((7 - total_failed)); \
	if [ $$total_failed -eq 0 ]; then \
		echo "🎉 ALL CHAPTERS PASSED! ($$passed/7)"; \
		echo "✅ All chapter tests completed successfully!"; \
	else \
		echo "⚠️  $$passed/7 chapters passed, $$total_failed failed"; \
		echo "❌ Some tests failed. Check individual chapter outputs above."; \
	fi; \
	echo "=========================================="

# Run all chapter tests with Valgrind (Linux only)
test-all-valgrind:
	@echo "🔍 Running ALL chapter tests with Valgrind..."
	@echo "=========================================="
	@cd tests && make test-all-valgrind
	@echo "=========================================="
	@echo "✅ All chapter tests with Valgrind completed!"
	@echo "📋 Check valgrind_all.log in tests/ directory for details"

# --- DEMOS ---
clock: $(CLOCK_EXEC)
	@echo "🕐 Running clock demo..."
	$(RUNNER) ./$(CLOCK_EXEC)

$(CLOCK_EXEC): $(CLOCK_SRC) $(CLOCK_OBJS) $(LIBFT_LIB) $(MLX_TARGET)
	@echo "🔨 Compiling clock demo: $(CLOCK_EXEC)"
	$(CC) $(CFLAGS) -o $(CLOCK_EXEC) $(CLOCK_SRC) $(CLOCK_OBJS) $(LIBFT_FLAGS) $(MLX_LIB)

sphere: $(SPHERE_EXEC)
	@echo "🔴 Running sphere render demo..."
	$(RUNNER) ./$(SPHERE_EXEC)

$(SPHERE_EXEC): $(SPHERE_SRC) $(SPHERE_OBJS) $(LIBFT_LIB) $(MLX_TARGET)
	@echo "🔨 Compiling sphere demo: $(SPHERE_EXEC)"
	$(CC) $(CFLAGS) -o $(SPHERE_EXEC) $(SPHERE_SRC) $(SPHERE_OBJS) $(LIBFT_FLAGS) $(MLX_LIB)

# --- END of DEMOS ---

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Build the main miniRT project"
	@echo ""
	@echo "📚 TESTING:"
	@echo "  test-all         - Run ALL chapter tests (ch1-ch7)"
	@echo "  test-all-valgrind - Run ALL chapter tests with Valgrind"
	@echo "  test-ch1         - Run Chapter 1 tests"
	@echo "  test-ch2         - Run Chapter 2 tests"
	@echo "  test-ch3         - Run Chapter 3 tests"
	@echo "  test-ch4         - Run Chapter 4 tests"
	@echo "  test-ch5         - Run Chapter 5 tests"
	@echo "  test-ch6         - Run Chapter 6 tests"	
	@echo "  test-ch7         - Run Chapter 7 tests"
	@echo ""
	@echo "🎮 DEMOS:"
	@echo "  clock            - Run clock face demo (Chapter 4)"
	@echo "  sphere           - Run sphere render demo (Chapter 5 and 6)"
	@echo ""
	@echo "🔧 MAINTENANCE:"
	@echo "  clean            - Remove object files"
	@echo "  fclean           - Remove object files and executables"
	@echo "  re               - Rebuild everything"
	@echo "  help             - Show this help message"
	@echo ""
	@echo "Current OS: $(UNAME_S)"

.PHONY: all clean fclean re test-ch1 test-ch2 test-ch3 test-ch4 test-ch5 test-ch6 test-ch7 test-all test-all-valgrind help clock sphere

#!!!DELETE valgrind.log as well
# rm -f valgrind.log  # <-- to delete later
#!!!DELETE mlx.supp with valgrind mlx suppression rules

# Create test_file:						tests/test_matrices.c
# Compile:								make test_matrices
# Compile till 'Matrices' + valgrind:	make vbtest
# Compile all tests from 'Matrices:		make newtests
