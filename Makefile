# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 20:32:02 by ycantin           #+#    #+#              #
#    Updated: 2025/05/15 15:44:51 by ycantin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a 
NAME = cub3D
CC = cc
FLAGS = -Wall -Werror -Wextra -g
DEPS = -Iminilibx-linux -Lminilibx-linux -lmlx -lXext -lX11 -lm -O3
RM = rm -f

SRC = 	main.c \
		clean_exit.c \
		parsing/parse.c \
		parsing/parse_utils.c \
		parsing/flood.c \
		parsing/flood_utils.c \
		parsing/bufferize.c \
		parsing/measure_map.c \
		movement.c \
		draw_map.c \
		rendering/pixels_and_color.c \
		rendering/delta_time.c \
		raycaster/raycaster.c  raycaster/raycaster_utils.c	raycaster/raycaster_utils2.c \
		mlx/mlx_handling.c \
		mlx/textures.c

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(SRC)
	@$(CC) $(FLAGS) $(SRC) $(LIBFT) -o $(NAME) $(DEPS)

clean:
#	@$(RM) $(OBJ)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all