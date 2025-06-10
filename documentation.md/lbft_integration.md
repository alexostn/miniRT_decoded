- miniRT/
  - Makefile          # <-- Ваш главный Makefile, который мы будем изменять
  - libft/            # <-- Папка с вашей библиотекой
    - Makefile        # <-- Makefile самой libft
    - *.c             # <-- Исходные файлы libft
    - libft.h
  - src/
  - include/
  - mlx-linux/
  - ...
NAME    = miniRT
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -Iinclude -Imlx-linux

# --- Переменные для Libft --- # <<< ИЗМЕНЕНИЕ
LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# --- Переменные для MiniLibX ---
MLX_DIR = mlx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# --- Переменные проекта ---
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
			$(SRC_DIR)/tuples/pixel.c

OBJS    = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# --- Переменные для тестов из книги ---
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
						$(SRC_DIR)/tuples/pixel.c
BOOK_TEST_MODULE_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BOOK_TEST_MODULE_SRCS))
BOOK_TEST_RUNNER_OBJ = $(OBJ_DIR)/$(BOOK_TEST_RUNNER_SRC:.c=.o)
BOOK_TEST_EXECUTABLE = run_book_tests

# --- Основные правила ---
all: $(NAME)

# Правило для компиляции libft # <<< ИЗМЕНЕНИЕ
$(LIBFT_LIB):
	@make -s -C $(LIBFT_DIR)

# Правило для компиляции mlx
$(MLX_DIR)/libmlx.a:
	@make -s -C $(MLX_DIR)

# Обновленное правило для сборки miniRT # <<< ИЗМЕНЕНИЕ
$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_DIR)/libmlx.a
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAGS) $(MLX_LIB) -o $(NAME)

# Правило для компиляции .c -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# --- Правила для тестов из книги ---
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

# Обновленное правило для сборки исполняемого файла тестов # <<< ИЗМЕНЕНИЕ
$(BOOK_TEST_EXECUTABLE): $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS) $(LIBFT_LIB) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $^ $(LIBFT_FLAGS) $(MLX_LIB) -o $@

# --- Правила очистки ---
clean:
	@make -s -C $(LIBFT_DIR) clean # <<< ИЗМЕНЕНИЕ
	@make -s -C $(MLX_DIR) clean
	rm -f $(OBJS)
	rm -f $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -s -C $(LIBFT_DIR) fclean # <<< ИЗМЕНЕНИЕ
	rm -f $(NAME)
	rm -f $(BOOK_TEST_EXECUTABLE)
	rm -f valgrind.log

re: fclean all

.PHONY: all clean fclean re btest vbtest