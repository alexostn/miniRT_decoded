# Makefile for miniRT (C, miniLibX, no malloc)
NAME    = miniRT
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -Iinclude -I$(LIBFT_DIR) -I$(LIBFT_DIR)/inc -I$(MLX_DIR) -I/usr/include  # >>> Добавлен /usr/include для X11
# CFLAGS  = -Wall -Wextra -Werror -g -Iinclude -Imlx-linux #-g is for debugger DELETE IT LATER

# Libft variables:
LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# MiniLibX variables:
MLX_DIR = mlx-linux  # >>> Убедитесь, что имя папки совпадает с реальным (mlx_linux/mlx-linux)
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lbsd -lm -lz  # >>> Добавлен -lbsd

# Project variables:
SRC_DIR = src
OBJ_DIR = obj

SRCS    = $(SRC_DIR)/main.c \
			$(SRC_DIR)/window.c \
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
			$(SRC_DIR)/tuples/image_to_ppm.c

OBJS    = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Variables for booktests:
BOOK_TEST_RUNNER_SRC = book_tests.c

BOOK_TEST_MODULE_SRCS = $(SRC_DIR)/tuples/tuple_creation.c \
						$(SRC_DIR)/window.c \
						$(SRC_DIR)/image.c \
						$(SRC_DIR)/tuples/tuple_predicates.c \
						$(SRC_DIR)/tuples/tuple_utils.c \
						$(SRC_DIR)/tuples/tuple_multiply_divide.c \
						$(SRC_DIR)/tuples/tuple_magitude_normalize_dot.c \
						$(SRC_DIR)/phisics/projectile.c \
						$(SRC_DIR)/tuples/colors.c \
						$(SRC_DIR)/tuples/color_converters.c \
						$(SRC_DIR)/tuples/pixel.c \
						$(SRC_DIR)/tuples/image_to_ppm.c

BOOK_TEST_MODULE_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BOOK_TEST_MODULE_SRCS))

BOOK_TEST_RUNNER_OBJ = $(OBJ_DIR)/$(BOOK_TEST_RUNNER_SRC:.c=.o)
BOOK_TEST_EXECUTABLE = run_book_tests

# Basic rules:
all: $(NAME)

# Libft compilation rule:
$(LIBFT_LIB):
	@make -s -C $(LIBFT_DIR)
	
# MLX compilation rule:
$(MLX_DIR)/libmlx.a:
	@make -s -C $(MLX_DIR)
	
# miniRT compilation rule:
$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_DIR)/libmlx.a
	$(CC) $(OBJS) $(LIBFT_FLAGS) $(MLX_LIB) -o $(NAME)  # >>> Убраны CFLAGS из линковки

# Правило для компиляции .c из src/ в obj/ 
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)  # Автоматическое создание вложенных папок
	$(CC) $(CFLAGS) -c $< -o $@

# >>> BOOK TESTS SECTION START >>>
$(BOOK_TEST_RUNNER_OBJ): $(BOOK_TEST_RUNNER_SRC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

btest: $(BOOK_TEST_EXECUTABLE)
	@echo "Running Raytracer Challenge book tests..."
	./$(BOOK_TEST_EXECUTABLE)
	@echo "Book tests finished."

vbtest: $(BOOK_TEST_EXECUTABLE)
	@echo "Running Raytracer Challenge book tests with Valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --suppressions=mlx.supp \
	--log-file=valgrind.log ./$(BOOK_TEST_EXECUTABLE)
	@echo "Valgrind tests finished. See valgrind.log for details."

$(BOOK_TEST_EXECUTABLE): $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS) $(LIBFT_LIB) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $^ $(LIBFT_FLAGS) $(MLX_LIB) -o $@

# Clean rules:
clean:
	@make -s -C $(LIBFT_DIR) clean
	@make -s -C $(MLX_DIR) clean
	rm -f $(OBJS)
	rm -f $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -s -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm -f $(BOOK_TEST_EXECUTABLE)
	rm -f valgrind.log

re: fclean all
.PHONY: all clean fclean re btest vbtest
