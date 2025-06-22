# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 17:57:48 by oostapen          #+#    #+#              #
#    Updated: 2025/06/12 23:53:14 by oostapen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for miniRT (C, miniLibX, no malloc)
NAME    = miniRT
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -Iinclude -I$(LIBFT_DIR) -I$(LIBFT_DIR)/inc -I$(MLX_DIR)
# CFLAGS  = -Wall -Wextra -Werror -g -Iinclude -Imlx-linux #-g is for debugger DELETE IT LATER

# Libft variables:
LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# MiniLibX variables:
MLX_DIR = mlx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz
# previous:
# MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Project variables:2
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
# 1. Исходный файл с тестами книги (лежит в корне проекта)
BOOK_TEST_RUNNER_SRC = book_tests.c

# 2. Исходные файлы из твоего проекта src/, которые нужны для тестов книги
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

# 3. Объектные файлы для модулей, используемых тестами
BOOK_TEST_MODULE_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BOOK_TEST_MODULE_SRCS))

# 4. Объектный файл для самого test runner'а
#    Он будет создан в $(OBJ_DIR)/book_tests.o
BOOK_TEST_RUNNER_OBJ = $(OBJ_DIR)/$(BOOK_TEST_RUNNER_SRC:.c=.o)

# 5. Имя исполняемого файла для тестов книги
BOOK_TEST_EXECUTABLE = run_book_tests

# bASic rules:
all: $(NAME)
# all: $(MLX_DIR)/libmlx.a $(NAME)			OLD

# libft compilation rule:
$(LIBFT_LIB):
	@make -s -C $(LIBFT_DIR)
	
# to avoid mistakes with Makefile.gen we compile it in advance:
$(MLX_DIR)/Makefile.gen:
	cd $(MLX_DIR) && ./configure

# MLX compilation rule:
$(MLX_DIR)/libmlx.a: $(MLX_DIR)/Makefile.gen
	@make -s -C $(MLX_DIR)

# miniRT compilation rule:
$(NAME): $(OBJS) $(LIBFT_LIB) $(MLX_DIR)/libmlx.a
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT_FLAGS) $(MLX_LIB) -o $(NAME)

# $(NAME): $(OBJS)							OLD
# 	$(CC) $(OBJS) $(CFLAGS) $(MLX_LIB) -o $(NAME)

# Правило для компиляции .c из src/ в obj/ (для основного проекта и модулей тестов)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# >>> BOOK TESTS SECTION START (RULES) >>>
# Правило для компиляции book_tests.c в obj/book_tests.o
$(BOOK_TEST_RUNNER_OBJ): $(BOOK_TEST_RUNNER_SRC)
	@mkdir -p $(OBJ_DIR) # Убедимся, что obj/ существует
	$(CC) $(CFLAGS) -c $< -o $@

# Цель для сборки и запуска тестов книги
btest: $(BOOK_TEST_EXECUTABLE)
	@echo "Running Raytracer Challenge book tests..."
	./$(BOOK_TEST_EXECUTABLE)
	@echo "Book tests finished."

# Добавляем цель для запуска тестов с Valgrind
vbtest: $(BOOK_TEST_EXECUTABLE)
	@echo "Running Raytracer Challenge book tests with Valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --suppressions=mlx.supp \
	--log-file=valgrind.log ./$(BOOK_TEST_EXECUTABLE)
	@echo "Valgrind tests finished. See valgrind.log for details."

# tests compilation rules:
$(BOOK_TEST_EXECUTABLE): $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS) $(LIBFT_LIB) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $^ $(LIBFT_FLAGS) $(MLX_LIB) -o $@

# OLD:
# $(BOOK_TEST_EXECUTABLE): $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS) $(MLX_DIR)/libmlx.a
# 	$(CC) $(CFLAGS) $^ $(MLX_LIB) -lm -o $@
#  -lm включает все зависимости продублирован уже здесь есть:
# MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# clean rules:
clean:
	@make -s -C $(LIBFT_DIR) clean # <<< ИЗМЕНЕНИЕ
	@make -s -C $(MLX_DIR) clean
	rm -f $(OBJS)
	rm -f $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS)
	rm -rf $(OBJ_DIR)
# clean:
# 	rm -f $(OBJS)
# 	rm -f $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS)
# 	@make -s -C $(MLX_DIR) clean

fclean: clean
	@make -s -C $(LIBFT_DIR) fclean # <<< ИЗМЕНЕНИЕ
	rm -f $(NAME)
	rm -f $(BOOK_TEST_EXECUTABLE)
	rm -f valgrind.log
# fclean: clean
# 	rm -f $(NAME)
# 	rm -f $(BOOK_TEST_EXECUTABLE)
# 	rm -f valgrind.log  # <-- to delete later
# 	rm -rf $(OBJ_DIR)

re: fclean all
.PHONY: all clean fclean re btest vbtest # vbtest is compilation for valgrind TO DELETE LATER

#!!!DELETE valgrind.log as well
# rm -f valgrind.log  # <-- to delete later
#!!!DELETE mlx.supp with valgrind mlx suppression rules