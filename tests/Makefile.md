# Makefile for The Raytracer Challenge Book Tests (ULTRA-ROBUST FINAL VERSION)

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
LDFLAGS		= -L../libft -lft

TARGET		= run_test
SRC_DIR		= ../src
OBJ_DIR		= obj
CHAPTERS_DIR = chapters

# --- ИСХОДНЫЕ ФАЙЛЫ ---

SRCS_ROOT = window.c image.c init.c
SRCS_TUPLES = tuples/tuple_creation.c tuples/tuple_predicates.c tuples/tuple_utils.c \
			  tuples/tuple_multiply_divide.c tuples/tuple_magitude_normalize_dot.c \
			  tuples/colors.c tuples/color_converters.c tuples/pixel.c tuples/image_to_ppm.c
SRCS_MATRICES = matrices/matrices.c matrices/matrice_creation.c matrices/matrice_operations.c \
				matrices/matrice_inverse.c matrices/matrice_submatrix.c matrices/transformations.c \
				matrices/matrice_determinant_API.c matrices/matrice_determinant_recursive.c \
				matrices/matrice_rotation.c
SRCS_PHYSICS = phisics/projectile.c
SRCS_RAYS = rays/rays.c
SRCS_SPHERES = spheres/spheres.c spheres/intersections_utils.c
SRCS_MATH = math/math_utils.c

TEST_SRCS_ROOT = test_common.c test_runner.c
TEST_SRCS_CH = chapters/test_chapter1.c chapters/test_chapter2.c chapters/test_chapter3.c \
			   chapters/test_chapter4.c chapters/test_chapter5.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS_ROOT:.c=.o)) \
	   $(addprefix $(OBJ_DIR)/, $(SRCS_TUPLES:.c=.o)) \
	   $(addprefix $(OBJ_DIR)/, $(SRCS_MATRICES:.c=.o)) \
	   $(addprefix $(OBJ_DIR)/, $(SRCS_PHYSICS:.c=.o)) \
	   $(addprefix $(OBJ_DIR)/, $(SRCS_RAYS:.c=.o)) \
	   $(addprefix $(OBJ_DIR)/, $(SRCS_SPHERES:.c=.o)) \
	   $(addprefix $(OBJ_DIR)/, $(SRCS_MATH:.c=.o)) \
	   $(addprefix $(OBJ_DIR)/, $(TEST_SRCS_ROOT:.c=.o)) \
	   $(addprefix $(OBJ_DIR)/, $(TEST_SRCS_CH:.c=.o))

# --- БИБЛИОТЕКИ ---

MLX_DIR		= ../mlx-linux
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
INCLUDES	= -I../include -I$(MLX_DIR) -I../libft/inc

# --- ОСНОВНЫЕ ПРАВИЛА ---

.PHONY: all test run_test vtest clean fclean re dirs

all: $(TARGET)

$(TARGET): $(OBJS) ../libft/libft.a
$(CC) $(OBJS) -o $@ $(LDFLAGS) $(MLX_FLAGS)

test: all
	./$(TARGET)

run_test: test

vtest: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

re: fclean all

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TARGET)

# --- ПРАВИЛА КОМПИЛЯЦИИ ---

dirs:
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/tuples $(OBJ_DIR)/matrices $(OBJ_DIR)/phisics \
	$(OBJ_DIR)/rays $(OBJ_DIR)/spheres $(OBJ_DIR)/math $(OBJ_DIR)/chapters

# Правила для каждой подпапки
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | dirs
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/tuples/%.o: $(SRC_DIR)/tuples/%.c | dirs
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/matrices/%.o: $(SRC_DIR)/matrices/%.c | dirs
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/phisics/%.o: $(SRC_DIR)/phisics/%.c | dirs
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/rays/%.o: $(SRC_DIR)/rays/%.c | dirs
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/spheres/%.o: $(SRC_DIR)/spheres/%.c | dirs
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/math/%.o: $(SRC_DIR)/math/%.c | dirs
$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Правила для тестов
$(OBJ_DIR)/%.o: %.c | dirs
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/chapters/%.o: $(CHAPTERS_DIR)/%.c | dirs
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
