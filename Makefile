# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 17:57:48 by oostapen          #+#    #+#              #
#    Updated: 2025/09/11 20:27:26 by oostapen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for miniRT (C, miniLibX, no malloc)
NAME    = miniRT
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -Iinclude -Itests/ -I$(LIBFT_DIR) -I$(LIBFT_DIR)/inc -I$(MLX_DIR)

# Libft variables:
LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# MiniLibX variables:
MLX_DIR = mlx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

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
			$(SRC_DIR)/tuples/image_to_ppm.c \
			$(SRC_DIR)/matrices/matrices.c \
			$(SRC_DIR)/matrices/matrice_creation.c \
			$(SRC_DIR)/matrices/matrice_operations.c \
			$(SRC_DIR)/matrices/matrice_inverse.c \
			$(SRC_DIR)/matrices/matrice_submatrix.c \
			$(SRC_DIR)/matrices/transformations.c \
			$(SRC_DIR)/matrices/matrice_determinant_API.c\
			$(SRC_DIR)/matrices/matrice_determinant_recursive.c

OBJS    = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Variables for booktests:
# 1. Source file with book tests (located in the project root)
BOOK_TEST_RUNNER_SRC = book_tests.c

# 2. Source files from your src/ project needed for the book tests
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
						$(SRC_DIR)/tuples/image_to_ppm.c \
						$(SRC_DIR)/matrices/matrices.c \
						$(SRC_DIR)/matrices/matrice_creation.c \
						$(SRC_DIR)/matrices/matrice_operations.c \
						$(SRC_DIR)/matrices/matrice_inverse.c \
						$(SRC_DIR)/matrices/matrice_submatrix.c \
						$(SRC_DIR)/matrices/transformations.c \
						$(SRC_DIR)/matrices/matrice_determinant_API.c\
						$(SRC_DIR)/matrices/matrice_determinant_recursive.c

# 3. Object files for modules used by the tests
BOOK_TEST_MODULE_OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(BOOK_TEST_MODULE_SRCS))

# 4. Object file for the test runner itself
#    It will be created in $(OBJ_DIR)/book_tests.o
BOOK_TEST_RUNNER_OBJ = $(OBJ_DIR)/$(BOOK_TEST_RUNNER_SRC:.c=.o)

# 5. Name of the executable file for the book tests
BOOK_TEST_EXECUTABLE = run_book_tests

# >>> MODULE TESTING SECTION BEGINNING
# New tests (automatic discovery)
TESTS_DIR = tests
TEST_SOURCES = $(wildcard $(TESTS_DIR)/test_*.c)
TEST_BINS = $(patsubst $(TESTS_DIR)/%.c, $(TESTS_DIR)/%, $(TEST_SOURCES))

# Rule for compiling ONE test
$(TESTS_DIR)/%: $(TESTS_DIR)/%.c $(BOOK_TEST_MODULE_OBJS) $(LIBFT_LIB) $(MLX_DIR)/libmlx.a
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ $(LIBFT_FLAGS) $(MLX_LIB) -o $@

# Rule for running ONE test
test_%: $(TESTS_DIR)/test_%
	@echo "Running $@..."
	./$<
	@echo "Test finished"

# Rule for running ALL new tests
newtests: $(TEST_BINS)
	@for t in $(notdir $(TEST_BINS)); do \
		echo "Running $$t..."; \
		./$(TESTS_DIR)/$$t; \
	done
# >>> MODULE TESTING SECTION END


# basic rules:
all: $(NAME)

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

# Rule for compiling .c from src/ to obj/ (for the main project and test modules)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# >>> BOOK TESTS SECTION START (RULES) >>>
# Rule for compiling book_tests.c into obj/book_tests.o
$(BOOK_TEST_RUNNER_OBJ): $(BOOK_TEST_RUNNER_SRC)
	@mkdir -p $(OBJ_DIR) # Убедимся, что obj/ существует
	$(CC) $(CFLAGS) -c $< -o $@

# Target for building and running the book tests
btest: $(BOOK_TEST_EXECUTABLE)
	@echo "Running Raytracer Challenge book tests..."
	./$(BOOK_TEST_EXECUTABLE)
	@echo "Book tests finished."

# Adding a target to run tests with Valgrind
vbtest: $(BOOK_TEST_EXECUTABLE)
	@echo "Running Raytracer Challenge book tests with Valgrind..."
	valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --suppressions=mlx.supp \
	--log-file=valgrind.log ./$(BOOK_TEST_EXECUTABLE)
	@echo "Valgrind tests finished. See valgrind.log for details."

# tests compilation rules:
$(BOOK_TEST_EXECUTABLE): $(BOOK_TEST_RUNNER_OBJ) $(BOOK_TEST_MODULE_OBJS) $(LIBFT_LIB) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $^ $(LIBFT_FLAGS) $(MLX_LIB) -o $@

# clean rules:
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
	rm -f $(TEST_BINS)
	rm -f valgrind.log

re: fclean all
.PHONY: all clean fclean re btest vbtest # vbtest is compilation for valgrind TO DELETE LATER

#!!!DELETE valgrind.log as well
# rm -f valgrind.log  # <-- to delete later
#!!!DELETE mlx.supp with valgrind mlx suppression rules

# Create test_file:						tests/test_matrices.c
# Compile:								make test_matrices
# Compile till 'Matrices' + valgrind:	make vbtest
# Compile all tests from 'Matrices:		make newtests