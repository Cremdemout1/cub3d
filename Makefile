# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 20:32:02 by ycantin           #+#    #+#              #
#    Updated: 2024/10/28 21:11:49 by ycantin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a 
NAME = cub3d
CC = cc
FLAGS = -Wall -Werror -Wextra -g
DEPS = -Iminilibx-linux -Lminilibx-linux -lmlx -lXext -lX11 -lm
RM = rm -f

SRC = main.c parse.c

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