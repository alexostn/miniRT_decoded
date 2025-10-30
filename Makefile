# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarherna <sarherna@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 17:57:48 by oostapen          #+#    #+#              #
#    Updated: 2025/10/30 09:51:26 by sarherna         ###   ########.fr        #
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

# ============================================================================ #
#                              COMMON SOURCES                                  #
# ============================================================================ #
# These sources are shared between mandatory and bonus
SRCS_COMMON	= $(SRC_DIR)/main.c \
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
			$(SRC_DIR)/computations/computations.c \
			$(SRC_DIR)/computations/computations_compat.c \
			$(SRC_DIR)/computations/object_lookup.c \
			$(SRC_DIR)/camera/camera.c \
			$(SRC_DIR)/camera/camera_orientation.c \
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
			$(SRC_DIR)/intersections/intersections.c \
			$(SRC_DIR)/intersections/utils.c \
			$(SRC_DIR)/scene/init_scene.c \
			$(SRC_DIR)/parser/parse_scene.c \
			$(SRC_DIR)/parser/parse_error.c \
			$(SRC_DIR)/parser/parse_ambient.c \
			$(SRC_DIR)/parser/parse_camera.c \
			$(SRC_DIR)/parser/parse_sphere.c \
			$(SRC_DIR)/parser/parser_color.c \
			$(SRC_DIR)/parser/parse_cylinder.c \
			$(SRC_DIR)/parser/parse_plane.c \
			$(SRC_DIR)/parser/parse_validate.c \
			$(SRC_DIR)/parser/helpers/parser_numbers.c \
			$(SRC_DIR)/parser/helpers/parser_orientation.c \
			$(SRC_DIR)/utils/save_ppm_utils.c

# ============================================================================ #
#                            MANDATORY SOURCES                                 #
# ============================================================================ #
# Mandatory: single light, no cones
SRCS_MANDATORY = $(SRCS_COMMON) \
			$(SRC_DIR)/mandatory/parser/parse_internal_mandatory.c \
			$(SRC_DIR)/mandatory/parser/parse_light_mandatory.c \
			$(SRC_DIR)/mandatory/computations/shade_hit_mandatory.c \
			$(SRC_DIR)/mandatory/computations/lighting_support_mandatory.c \
			$(SRC_DIR)/mandatory/world/world_intersect_mandatory.c

# ============================================================================ #
#                              BONUS SOURCES                                   #
# ============================================================================ #
# Bonus: multiple lights + cones
SRCS_BONUS = $(SRCS_COMMON) \
			$(SRC_DIR)/bonus/cones/cones_bonus.c \
			$(SRC_DIR)/bonus/cones/cone_intersect_bonus.c \
			$(SRC_DIR)/bonus/cones/cone_normal_bonus.c \
			$(SRC_DIR)/bonus/parser/parse_cone_bonus.c \
			$(SRC_DIR)/bonus/parser/parse_light_bonus.c \
			$(SRC_DIR)/bonus/parser/parse_internal_bonus.c \
			$(SRC_DIR)/bonus/parser/parser_cone_input_bonus.c \
			$(SRC_DIR)/bonus/parser/parser_cone_utils_bonus.c \
			$(SRC_DIR)/bonus/computations/shade_hit_bonus.c \
			$(SRC_DIR)/bonus/computations/lighting_support_bonus.c \
			$(SRC_DIR)/bonus/world/world_intersect_bonus.c

# Object file lists
OBJS_MANDATORY = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS_MANDATORY))
OBJS_BONUS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS_BONUS))

# Default target: build mandatory
.DEFAULT_GOAL := all

# ============================================================================ #
#                              BUILD RULES                                     #
# ============================================================================ #

all: $(NAME)

# Mandatory build
$(NAME): $(OBJS_MANDATORY) $(LIBFT_LIB) $(MLX_TARGET)
	$(CC) $(OBJS_MANDATORY) $(CFLAGS) $(LIBFT_FLAGS) $(MLX_LIB) -o $(NAME)
	@echo "✅ miniRT (MANDATORY) compiled successfully!"

# Bonus build
bonus: $(OBJS_BONUS) $(LIBFT_LIB) $(MLX_TARGET)
	$(CC) $(OBJS_BONUS) $(CFLAGS) $(LIBFT_FLAGS) $(MLX_LIB) -o $(NAME)
	@echo "✅ miniRT (BONUS) compiled successfully!"

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

# ============================================================================ #
#                              CLEAN RULES                                     #
# ============================================================================ #

clean:
	@make -s -C $(LIBFT_DIR) clean
	@make -s -C $(MLX_DIR) clean
	rm -rf $(OBJ_DIR)
	@echo "🧹 Cleaning output files..."

fclean: clean fclean_output
	@make -s -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f valgrind.log
	rm -f $(MLX_CLEAN_TARGET)
	@echo "✅ Full clean complete"


re: fclean all

# ============================================================================ #
#                              RUN RULES                                       #
# ============================================================================ #

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

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Build miniRT (MANDATORY: single light, no cones)"
	@echo "  bonus            - Build miniRT (BONUS: multiple lights + cones)"
	@echo ""
	@echo "🚀 RUNNING:"
	@echo "  run SCENE=<file> - Run miniRT with a scene file"
	@echo "  run SCENE=<file> V=1 - Run miniRT with Valgrind"
	@echo "  Example: make run SCENE=scenes/valid_scenes/simple_test.rt"
	@echo "  Example: make run SCENE=scenes/valid_scenes/simple_test.rt V=1"
	@echo ""
	@echo "🔧 MAINTENANCE:"
	@echo "  clean            - Remove object files"
	@echo "  clean_output     - Remove PPM files from output/"
	@echo "  fclean           - Remove all build artifacts + output/"
	@echo "  re               - Rebuild everything"
	@echo "  help             - Show this help message"
	@echo ""
	@echo "📁 OUTPUT:"
	@echo "  Rendered images are saved to: output/render_N.ppm"
	@echo "  Use 'make clean_output' to clean PPM files"
	@echo "  Use 'make fclean' to remove output/ completely"
	@echo ""
	@echo "Current OS: $(UNAME_S)"


# ============================================================================ #
#                       OUTPUT DIRECTORY MANAGEMENT                            #
# ============================================================================ #

OUTPUT_DIR = output

# Clean only PPM files from output directory
clean_output:
	@if [ -d "$(OUTPUT_DIR)" ]; then \
		rm -f $(OUTPUT_DIR)/*.ppm; \
		echo "🧹 Cleaned $(OUTPUT_DIR)/*.ppm"; \
	fi

# Remove output directory completely
fclean_output:
	@if [ -d "$(OUTPUT_DIR)" ]; then \
		rm -rf $(OUTPUT_DIR); \
		echo "🗑️  Removed $(OUTPUT_DIR)/ directory"; \
	fi

.PHONY: all bonus clean fclean re run help clean_output fclean_output
