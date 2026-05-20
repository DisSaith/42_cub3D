# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/28 17:01:03 by acohaut           #+#    #+#              #
#    Updated: 2026/05/20 12:43:19 by acohaut          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g
NAME		= cub3D
INCLUDES	= -I includes -I./libft

LIBFT		= libft/libft.a

SRCS		= 	srcs/main.c \
				srcs/parsing/parsing.c \
				srcs/parsing/file_parsing.c \
				srcs/parsing/map_parsing.c \
				srcs/parsing/textures_parsing.c \
				srcs/parsing/rgb_parsing.c \
				srcs/parsing/player_parsing.c \
				srcs/parsing/utils_parsing.c \
				srcs/rendering/rendering.c \
				srcs/rendering/mini_map.c \
				srcs/rendering/load_textures.c \
				srcs/rendering/raycasting.c \
				srcs/utilities/utils_cub3d.c \
				srcs/utilities/free.c \
				srcs/utilities/error.c \
				srcs/utilities/initialize_game.c \
				srcs/utilities/key_manager.c \
				srcs/utilities/move_player.c \


OBJS		= $(SRCS:srcs/%.c=objs/%.o)

all:		$(NAME)

$(LIBFT):
		make -C libft

objs/%.o: srcs/%.c 
		mkdir -p $(@D)
		$(CC) $(CFLAGS) $(INCLUDES) -I/usr/include -Imlx_linux -c $< -o $@


$(NAME):	$(LIBFT) $(OBJS)
		make -C mlx_linux
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
		rm -rf objs/
		make clean -C libft

fclean:		clean
		rm -f $(NAME)
		make fclean -C libft

re:		fclean all

.PHONY:		all clean fclean re bonus
