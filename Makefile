# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/28 17:01:03 by acohaut           #+#    #+#              #
#    Updated: 2026/05/21 11:14:49 by acohaut          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
NAME		= cub3D
NAME_BONUS	= cub3D_bonus
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
				srcs/rendering/load_textures.c \
				srcs/rendering/raycasting.c \
				srcs/utilities/utils_cub3d.c \
				srcs/utilities/free.c \
				srcs/utilities/error.c \
				srcs/utilities/initialize_game.c \
				srcs/utilities/key_manager.c \
				srcs/utilities/move_player.c \

SRCS_BONUS =	srcs/bonus/main_bonus.c \
				srcs/bonus/minimap_bonus.c \
				srcs/bonus/raycasting_bonus.c \
				srcs/bonus/rendering_bonus.c \
				srcs/bonus/free_bonus.c \
				srcs/bonus/initialize_game_bonus.c \
				srcs/bonus/key_manager_bonus.c \
				srcs/bonus/move_player_bonus.c \
				srcs/parsing/parsing.c \
				srcs/parsing/file_parsing.c \
				srcs/parsing/map_parsing.c \
				srcs/parsing/textures_parsing.c \
				srcs/parsing/rgb_parsing.c \
				srcs/parsing/player_parsing.c \
				srcs/parsing/utils_parsing.c \
				srcs/rendering/load_textures.c \
				srcs/utilities/utils_cub3d.c \
				srcs/utilities/error.c \
				srcs/utilities/free.c \
				srcs/utilities/move_player.c \

OBJS		= $(SRCS:srcs/%.c=objs/%.o)

OBJS_BONUS	= $(SRCS_BONUS:srcs/%.c=objs/%.o)

all:		$(NAME)

$(LIBFT):
		make -C libft

objs/%.o: srcs/%.c 
		mkdir -p $(@D)
		$(CC) $(CFLAGS) $(INCLUDES) -I/usr/include -Imlx_linux -c $< -o $@

$(NAME):	$(LIBFT) $(OBJS)
		make -C mlx_linux
		$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

bonus:	$(LIBFT) $(OBJS_BONUS)
		make -C mlx_linux
		$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lXfixes -lm -lz -o $(NAME_BONUS)

clean:
		rm -rf objs/
		make clean -C libft

fclean:		clean
		rm -f $(NAME)
		rm -f $(NAME_BONUS)
		make fclean -C libft

re:		fclean all

.PHONY:		all clean fclean re bonus
