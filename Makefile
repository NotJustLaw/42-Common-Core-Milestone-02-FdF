# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skuhlcke <skuhlcke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 17:32:53 by skuhlcke          #+#    #+#              #
#    Updated: 2025/06/13 16:13:48 by skuhlcke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME      = fdf

SRC_DIR   = src
GNL_DIR   = gnl
LIBFT_DIR = libft
MLX_DIR   = minilibx-linux

SRCS      = $(SRC_DIR)/fdf.c        \
			$(SRC_DIR)/map.c        \
			$(SRC_DIR)/map_utils.c  \
			$(SRC_DIR)/render.c     \
			$(SRC_DIR)/render_utils.c \
			$(SRC_DIR)/fdf_utils.c  \
			$(SRC_DIR)/fds_utils.c  \
			$(SRC_DIR)/fdf_utils_extra.c \
			$(GNL_DIR)/get_next_line_bonus.c \
			$(GNL_DIR)/get_next_line_utils_bonus.c

OBJS      = $(SRCS:.c=.o)

LIBFT     = $(LIBFT_DIR)/libft.a
MLX_LIBS  = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

CC        = gcc
CFLAGS    = -Wall -Wextra -Werror -g \
            -I$(SRC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(MLX_LIBS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/fdf.h $(SRC_DIR)/fdf_compat.h
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
