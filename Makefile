# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 17:57:48 by oostapen          #+#    #+#              #
#    Updated: 2025/10/25 04:52:11 by oostapen         ###   ########.fr        #
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
			$(SRC_DIR)/materials/materials.c \
			$(SRC_DIR)/materials/lighting.c \
			$(SRC_DIR)/lights/lights.c \
			$(SRC_DIR)/matrices/matrice_submatrix.c \
			$(SRC_DIR)/matrices/transformations.c \
			$(SRC_DIR)/matrices/matrice_determinant_API.c \
			$(SRC_DIR)/matrices/matrice_determinant_recursive.c \
			$(SRC_DIR)/math/math_utils.c \
			$(SRC_DIR)/matrices/matrice_rotation.c \
			$(SRC_DIR)/world/world.c \
			$(SRC_DIR)/world/world_add_object.c \
			$(SRC_DIR)/world/world_add_light.c \
			$(SRC_DIR)/world/world_intersect.c \
			$(SRC_DIR)/computations/computations.c \
			$(SRC_DIR)/computations/object_lookup.c \
			$(SRC_DIR)/computations/lighting_support.c \
			$(SRC_DIR)/camera/camera.c \
			$(SRC_DIR)/render/render.c \
			$(SRC_DIR)/shapes/shapes.c \
			$(SRC_DIR)/spheres/spheres.c \
			$(SRC_DIR)/spheres/sphere_intersect.c \
			$(SRC_DIR)/spheres/sphere_normal.c \
			$(SRC_DIR)/spheres/sphere_render_grid.c \
			$(SRC_DIR)/spheres/sphere_render_phong.c \
			$(SRC_DIR)/cylinders/cylinders.c \
			$(SRC_DIR)/cylinders/cylinder_intersect.c \
			$(SRC_DIR)/cylinders/cylinder_normal.c \
			$(SRC_DIR)/planes/planes.c \
			$(SRC_DIR)/planes/planes_intersect.c \
			$(SRC_DIR)/planes/plane_normal.c \
			$(SRC_DIR)/cones/cones.c \
			$(SRC_DIR)/cones/cone_intersect.c \
			$(SRC_DIR)/cones/cone_normal.c \
			$(SRC_DIR)/intersections/intersections.c \
			$(SRC_DIR)/intersections/utils.c \
			$(SRC_DIR)/scene/init_scene.c \
			$(SRC_DIR)/parser/parse_scene.c \
			$(SRC_DIR)/parser/parse_internal.c \
			$(SRC_DIR)/parser/parse_error.c \
			$(SRC_DIR)/parser/parse_ambient.c \
			$(SRC_DIR)/parser/parse_camera.c \
			$(SRC_DIR)/parser/parse_light.c \
			$(SRC_DIR)/parser/parse_sphere.c \
			$(SRC_DIR)/parser/parser_color.c \
			$(SRC_DIR)/parser/parse_validate.c \
			$(SRC_DIR)/parser/parse_cylinder.c \
			$(SRC_DIR)/parser/parse_cone.c \
			$(SRC_DIR)/parser/parse_plane.c \
			$(SRC_DIR)/parser/helpers/parser_numbers.c \
			$(SRC_DIR)/parser/helpers/parser_orientation.c

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

SHADOW_SRC      = demos/shadow_demo_main.c
SHADOW_EXEC     = shadow_demo
SHADOW_OBJS     = $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

WORLD_SRC       = demos/world_render_main.c
WORLD_EXEC      = world_demo
WORLD_OBJS      = $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

SCENE_SRC       = demos/scene_main.c
SCENE_EXEC      = scene_demo
SCENE_OBJS      = $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

# Planes demo (Chapter 9)
PLANES_SRC      = demos/planes_demo_main.c
PLANES_EXEC     = planes_demo
PLANES_OBJS     = $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

# Cylinders demo (Chapter 13)
CYLINDERS_SRC   = demos/cylinders_demo_main.c
CYLINDERS_EXEC  = cylinders_demo
CYLINDERS_OBJS  = $(filter-out $(OBJ_DIR)/main.o, $(OBJS))

# Demo utilities - shared by all demos
DEMO_UTILS_SRC  = demos/demo_utils.c
DEMO_UTILS_OBJ  = $(OBJ_DIR)/demos/demo_utils.o

$(DEMO_UTILS_OBJ): $(DEMO_UTILS_SRC)
	@mkdir -p $(OBJ_DIR)/demos
	$(CC) $(CFLAGS) -c $(DEMO_UTILS_SRC) -o $(DEMO_UTILS_OBJ)
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
	-@make -s -C tests fclean
	rm -f $(NAME)
	rm -f valgrind.log
	rm -f $(MLX_CLEAN_TARGET)
	rm -rf $(CLOCK_EXEC)
	rm -rf $(SPHERE_EXEC)
	rm -rf $(SHADOW_EXEC)	
	rm -rf $(WORLD_EXEC)
	rm -rf $(SCENE_EXEC)
	rm -rf $(PLANES_EXEC)
	rm -rf $(CYLINDERS_EXEC)
	rm -rf demos/output

re: fclean all

# --- RUN WITH OPTIONAL VALGRIND ---
# Usage: make run SCENE=scenes/simple_test.rt [V=1]
# Example: make run SCENE=scenes/simple_test.rt V=1
run: $(NAME)
	@if [ -z "$(SCENE)" ]; then \
		echo "Error: Please specify SCENE=<file.rt>"; \
		echo "Usage: make run SCENE=scenes/simple_test.rt [V=1]"; \
		exit 1; \
	fi
	@echo "🚀 Running miniRT with $(SCENE)"
ifeq ($(V),1)
	@echo "🔍 Running with Valgrind..."
	$(RUNNER) ./$(NAME) $(SCENE)
else
	./$(NAME) $(SCENE)
endif

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

test-ch8:
	cd tests && make test-ch8

test-ch9:
	cd tests && make test-ch9

test-ch13:
	cd tests && make test-ch13

test-parser: $(MLX_TARGET)
	cd tests && make test-parser

# Run all chapter tests
test-all:
	@echo "🚀 Running ALL chapter tests..."
	@echo "=========================================="
	@ch1_result=0; ch2_result=0; ch3_result=0; ch4_result=0; ch5_result=0; ch6_result=0; ch7_result=0; ch8_result=0; \
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
	echo "Running Chapter 8 tests..."; \
	$(MAKE) test-ch8 > /dev/null 2>&1; ch8_result=$$?; \
	if [ $$ch8_result -eq 0 ]; then \
		echo "Chapter 8: ✅ PASSED"; \
	else \
		echo "Chapter 8: ❌ FAILED"; \
	fi; \
	echo ""; \
	echo "Running Chapter 9 tests..."; \
	$(MAKE) test-ch9 > /dev/null 2>&1; ch9_result=$$?; \
	if [ $$ch9_result -eq 0 ]; then \
		echo "Chapter 9: ✅ PASSED"; \
	else \
		echo "Chapter 9: ❌ FAILED"; \
	fi; \
	echo ""; \
	echo "Running Chapter 13 tests..."; \
	$(MAKE) test-ch13 > /dev/null 2>&1; ch13_result=$$?; \
	if [ $$ch13_result -eq 0 ]; then \
		echo "Chapter 13: ✅ PASSED"; \
	else \
		echo "Chapter 13: ❌ FAILED"; \
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
	if [ $$ch8_result -ne 0 ]; then total_failed=$$((total_failed + 1)); fi; \
	if [ $$ch9_result -ne 0 ]; then total_failed=$$((total_failed + 1)); fi; \
	if [ $$ch13_result -ne 0 ]; then total_failed=$$((total_failed + 1)); fi; \
	passed=$$((10 - total_failed)); \
	if [ $$total_failed -eq 0 ]; then \
		echo "🎉 ALL CHAPTERS PASSED! ($$passed/10)"; \
		echo "✅ All chapter tests completed successfully!"; \
	else \
		echo "⚠️  $$passed/10 chapters passed, $$total_failed failed"; \
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

$(CLOCK_EXEC): $(CLOCK_SRC) $(CLOCK_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_LIB) $(MLX_TARGET)
	$(CC) $(CFLAGS) -o $(CLOCK_EXEC) $(CLOCK_SRC) $(CLOCK_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_FLAGS) $(MLX_LIB)


sphere: $(SPHERE_EXEC)
	@echo "🔴 Running sphere render demo..."
	$(RUNNER) ./$(SPHERE_EXEC)

$(SPHERE_EXEC): $(SPHERE_SRC) $(SPHERE_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_LIB) $(MLX_TARGET)
	$(CC) $(CFLAGS) -o $(SPHERE_EXEC) $(SPHERE_SRC) $(SPHERE_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_FLAGS) $(MLX_LIB)


shadow: $(SHADOW_EXEC)
	@echo "🌒 Rendering shadow demo..."
	$(RUNNER) ./$(SHADOW_EXEC)

$(SHADOW_EXEC): $(SHADOW_SRC) $(SHADOW_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_LIB) $(MLX_TARGET)
	$(CC) $(CFLAGS) -o $(SHADOW_EXEC) $(SHADOW_SRC) $(SHADOW_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_FLAGS) $(MLX_LIB)

world: $(WORLD_EXEC)
	@echo "🌒 Rendering world demo..."
	$(RUNNER) ./$(WORLD_EXEC)

$(WORLD_EXEC): $(WORLD_SRC) $(WORLD_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_LIB) $(MLX_TARGET)
	$(CC) $(CFLAGS) -o $(WORLD_EXEC) $(WORLD_SRC) $(WORLD_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_FLAGS) $(MLX_LIB)

scene: $(SCENE_EXEC)
	@echo "🎬 Rendering Chapter 7 'Putting It Together' scene..."
	$(RUNNER) ./$(SCENE_EXEC)

$(SCENE_EXEC): $(SCENE_SRC) $(SCENE_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_LIB) $(MLX_TARGET)
	$(CC) $(CFLAGS) -o $(SCENE_EXEC) $(SCENE_SRC) $(SCENE_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_FLAGS) $(MLX_LIB)

planes: $(PLANES_EXEC)
	@echo "🛫 □ Rendering planes demo..."
	$(RUNNER) ./$(PLANES_EXEC)

$(PLANES_EXEC): $(PLANES_SRC) $(PLANES_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_LIB) $(MLX_TARGET)
	$(CC) $(CFLAGS) -o $(PLANES_EXEC) $(PLANES_SRC) $(PLANES_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_FLAGS) $(MLX_LIB)

# Cylinders demo
cylinders: $(CYLINDERS_EXEC)
	@echo "🛢 Rendering cylinders demo..."
	$(RUNNER) ./$(CYLINDERS_EXEC)

$(CYLINDERS_EXEC): $(CYLINDERS_SRC) $(CYLINDERS_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_LIB) $(MLX_TARGET)
	$(CC) $(CFLAGS) -o $(CYLINDERS_EXEC) $(CYLINDERS_SRC) $(CYLINDERS_OBJS) $(DEMO_UTILS_OBJ) $(LIBFT_FLAGS) $(MLX_LIB)

# --- END of DEMOS! ---

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Build the main miniRT project!"
	@echo ""
	@echo "� RUNNING:"
	@echo "  run SCENE=<file> - Run miniRT with a scene file"
	@echo "  run SCENE=<file> V=1 - Run miniRT with Valgrind"
	@echo "  Example: make run SCENE=scenes/simple_test.rt"
	@echo "  Example: make run SCENE=scenes/simple_test.rt V=1"
	@echo ""
	@echo "📚 TESTING:"
	@echo "  run_test         - Run ALL chapter tests (ch1-ch13)"
	@echo "  test-all-valgrind - Run ALL chapter tests with Valgrind"
	@echo "  test-ch1         - Run Chapter 1 tests"
	@echo "  test-ch2         - Run Chapter 2 tests"
	@echo "  test-ch3         - Run Chapter 3 tests"
	@echo "  test-ch4         - Run Chapter 4 tests"
	@echo "  test-ch5         - Run Chapter 5 tests"
	@echo "  test-ch6         - Run Chapter 6 tests"	
	@echo "  test-ch7         - Run Chapter 7 tests"
	@echo "  test-ch8         - Run Chapter 8 tests"
	@echo "  test-ch9         - Run Chapter 9 tests"
	@echo "  test-ch13        - Run Chapter 13 tests"
	@echo "  test-parser      - Run parser test"
	@echo ""
	@echo "  test-ch1 V=1     - Run Chapter 1 tests with Valgrind"
	@echo "  test-ch2 V=1     - Run Chapter 2 tests with Valgrind"
	@echo "  test-ch3 V=1     - Run Chapter 3 tests with Valgrind"
	@echo "  test-ch4 V=1     - Run Chapter 4 tests with Valgrind"
	@echo "  test-ch5 V=1     - Run Chapter 5 tests with Valgrind"
	@echo "  test-ch6 V=1     - Run Chapter 6 tests with Valgrind"	
	@echo "  test-ch7 V=1     - Run Chapter 7 tests with Valgrind"
	@echo "  test-ch8 V=1     - Run Chapter 8 tests with Valgrind"
	@echo "  test-ch9 V=1     - Run Chapter 9 tests with Valgrind"
	@echo "  test-ch13 V=1    - Run Chapter 13 tests with Valgrind"
	@echo ""
	@echo "🎮 DEMOS:"
	@echo "  clock            - Run clock face demo (Chapter 4)"
	@echo "  sphere           - Run sphere render demo (Chapter 5 and 6)"
	@echo "  world            - Render Chapter 7 world demo own experiments to (Chapter 7)"
	@echo "  scene            - Render 'Putting It Together' scene (Chapter 7)"
	@echo "  shadow           - Render Chapter 8 shadow demo"
	@echo "  planes           - Render Chapter 9 planes demo"
	@echo "  cylinders        - Render Chapter 13 cylinders demo (PPM)"
	@echo ""
	@echo "🎮 DEMOS with Valgrind:"
	@echo "  clock V=1        - Run clock face demo (Chapter 4) with Valgrind"
	@echo "  sphere V=1       - Run sphere render demo (Chapter 5 and 6) with Valgrind"
	@echo "  world V=1        - Render Chapter 7 world demo own experiments to (Chapter 7) with Valgrind"
	@echo "  scene V=1        - Render 'Putting It Together' scene (Chapter 7) with Valgrind"
	@echo "  shadow V=1       - Render Chapter 8 shadow demo with Valgrind"
	@echo "  planes V=1       - Render Chapter 9 planes demo with Valgrind"
	@echo "  cylinders V=1    - Render Chapter 13 cylinders demo (PPM) with Valgrind"
	@echo ""
	@echo "🔧 MAINTENANCE:"
	@echo "  clean            - Remove object files"
	@echo "  fclean           - Remove object files and executables"
	@echo "  re               - Rebuild everything"
	@echo "  help             - Show this help message"
	@echo ""
	@echo "Current OS: $(UNAME_S)"

.PHONY: all clean fclean re run test-ch1 test-ch2 test-ch3 test-ch4 test-ch5 test-ch6 test-ch7 test-ch8 test-ch9 test-ch13 test-parser test-all test-all-valgrind help clock sphere world shadow planes cylinders

#!!!DELETE valgrind.log as well
# rm -f valgrind.log  # <-- to delete later
#!!!DELETE mlx.supp with valgrind mlx suppression rules

# Create test_file:						tests/test_matrices.c
# Compile:								make test_matrices
# Compile till 'Matrices' + valgrind:	make vbtest
# Compile all tests from 'Matrices:		make newtests
