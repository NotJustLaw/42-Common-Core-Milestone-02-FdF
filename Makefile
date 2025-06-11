# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:32:53 by skuhlcke          #+#    #+#              #
#    Updated: 2025/06/11 14:48:56 by skuhlcke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      = fdf

# Source files
SRC_DIR   = src
GNL_DIR   = gnl
SRCS      = $(SRC_DIR)/fdf.c        \
            $(SRC_DIR)/map.c        \
            $(SRC_DIR)/map_utils.c  \
            $(SRC_DIR)/render.c     \
            $(SRC_DIR)/render_utils.c \
            $(SRC_DIR)/fdf_utils.c  \
			$(SRC_DIR)/fds_utils.c  \
			$(GNL_DIR)/get_next_line_bonus.c \
			$(GNL_DIR)/get_next_line_utils_bonus.c 

OBJS      = $(SRCS:.c=.o)

# Libraries
LIBFT_DIR = libft
LIBFT     = $(LIBFT_DIR)/libft.a

MLX_DIR   = minilibx-linux
MLX_INC   = -I$(MLX_DIR)
MLX_LIBS  = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

# Compiler
CC        = gcc
CFLAGS    = -Wall -Wextra -Werror -g -I$(SRC_DIR) -I$(LIBFT_DIR) $(MLX_INC)

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

# Build your libft first
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Compile and link
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(MLX_LIBS)

# Rule to compile .c → .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/fdf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all