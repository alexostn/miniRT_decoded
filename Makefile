# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 17:57:48 by oostapen          #+#    #+#              #
#    Updated: 2025/05/22 21:38:13 by oostapen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for miniRT (C, miniLibX, no malloc)
NAME    = miniRT
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -Iinclude -Imlx-linux
MLX_DIR = mlx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

SRC_DIR = src
OBJ_DIR = obj

SRCS    = $(SRC_DIR)/main.c \
			$(SRC_DIR)/window.c \
			$(SRC_DIR)/init.c \
			$(SRC_DIR)/tuples/tuple_creation.c \
			$(SRC_DIR)/tuples/tuple_predicates.c \
			$(SRC_DIR)/tuples/tuple_utils.c \
			$(SRC_DIR)/tuples/tuple_multiply_divide.c \
			$(SRC_DIR)/tuples/tuple_magitude_normalize_dot.c \
			# $(SRC_DIR)/tuples/ticks.c

OBJS    = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# 1. Исходный файл с тестами книги (лежит в корне проекта)
BOOK_TEST_RUNNER_SRC = book_tests.c

# 2. Исходные файлы из твоего проекта src/, которые нужны для тестов книги
BOOK_TEST_MODULE_SRCS = $(SRC_DIR)/tuples/tuple_creation.c \
						$(SRC_DIR)/tuples/tuple_predicates.c \
						$(SRC_DIR)/tuples/tuple_utils.c \
						$(SRC_DIR)/tuples/tuple_multiply_divide.c \
						$(SRC_DIR)/tuples/tuple_magitude_normalize_dot.c \
						# $(SRC_DIR)/tuples/ticks.c

# 3. Объектные файлы для модулей, используемых тестами
BOOK_TEST_MODULE_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BOOK_TEST_MODULE_SRCS))

# 4. Объектный файл для самого test runner'а
#    Он будет создан в $(OBJ_DIR)/book_tests.o
BOOK_TEST_RUNNER_OBJ = $(OBJ_DIR)/$(BOOK_TEST_RUNNER_SRC:.c=.o)

# 5. Имя исполняемого файла для тестов книги
BOOK_TEST_EXECUTABLE = run_book_tests

all: $(MLX_DIR)/libmlx.a $(NAME)

$(MLX_DIR)/libmlx.a:
	@make -s -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(MLX_LIB) -o $(NAME)
	
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
booktest: $(BOOK_TEST_EXECUTABLE)
	@echo "Running Raytracer Challenge book tests..."
	./$(BOOK_TEST_EXECUTABLE)
	@echo "Book tests finished."

# Сборка исполняемого файла для тестов книги
$(BOOK_TEST_EXECUTABLE): $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lm # $^ включает все зависимости

clean:
	rm -f $(OBJS)
	rm -f $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS)
	@make -s -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(BOOK_TEST_EXECUTABLE)
	rm -rf $(OBJ_DIR)

re: fclean all
.PHONY: all clean fclean re booktest
