# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oostapen <oostapen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/02 17:57:48 by oostapen          #+#    #+#              #
#    Updated: 2025/05/03 00:42:10 by oostapen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Minimal Makefile for miniRT (C, miniLibX, no malloc)
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
		 
OBJS    = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

all: $(MLX_DIR)/libmlx.a $(NAME)

$(MLX_DIR)/libmlx.a:
	@make -s -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(MLX_LIB) -o $(NAME)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	@make -s -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) -rf $(OBJ_DIR)
	

re: fclean all

.PHONY: all clean fclean re