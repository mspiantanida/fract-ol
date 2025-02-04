# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpiantan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/27 11:40:56 by mpiantan          #+#    #+#              #
#    Updated: 2025/01/09 16:53:17 by mpiantan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(MLX_DIR) -g
RM = rm -f

SRC_DIR = sources
INC_DIR = includes
LIB_DIR = libft
MLX_DIR = minilibx-linux

SRC_FILES = $(SRC_DIR)/fractol.c \
	    $(SRC_DIR)/fractol_input.c \
	    $(SRC_DIR)/fractol_calculator.c \
	    $(SRC_DIR)/fractol_display.c \
	    $(SRC_DIR)/fractol_render.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)

BONUS_SRC_FILES = $(SRC_DIR)/fractol_bonus.c \
	    $(SRC_DIR)/fractol_input_bonus.c \
	    $(SRC_DIR)/fractol_calculator_bonus.c \
	    $(SRC_DIR)/fractol_calculator_extra_bonus.c \
	    $(SRC_DIR)/fractol_display_bonus.c \
	    $(SRC_DIR)/fractol_render_bonus.c

BONUS_OBJ_FILES = $(BONUS_SRC_FILES:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)

MLX = $(MLX_DIR)/libmlx_Linux.a 
LIBFT = $(LIB_DIR)/libft.a

NAME = fractol


all: $(LIBFT) $(MLX) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz $(LIBFT) -o $(NAME)

bonus: $(LIBFT) $(MLX) $(BONUS_OBJ_FILES)
	$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz $(LIBFT) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make all -C $(LIB_DIR)
	
clean:
	$(RM) $(OBJ_FILES) $(BONUS_OBJ_FILES)
	make clean -C $(LIB_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all


.PHONY: all clean fclean re bonus
