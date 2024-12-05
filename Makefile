# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 20:32:02 by ycantin           #+#    #+#              #
#    Updated: 2024/12/05 11:47:14 by ycantin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a 
NAME = cub3d
CC = cc
FLAGS = -Wall -Werror -Wextra -g
DEPS = -Iminilibx-linux -Lminilibx-linux -lmlx -lXext -lX11 -lm
RM = rm -f

SRC = 	main.c \
		clean_exit.c \
		parsing/parse.c \
		parsing/flood.c \
		parsing/bufferize.c \
		measure.c \
		movement.c \
		draw_map.c \
		color.c \
		raycaster.c \
		my_mlx.c

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