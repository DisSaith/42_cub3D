# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/28 17:01:03 by acohaut           #+#    #+#              #
#    Updated: 2026/05/05 17:24:59 by nofelten         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= cc
CFLAGS		= -Wall -Wextra -Werror -g
NAME		= cub3D
INCLUDES	= -I includes -I./libft

LIBFT		= libft/libft.a

SRCS		= 	srcs/main.c \
				srcs/utils_cub3d.c \
				srcs/test_mlx.c \
				srcs/error.c \
				srcs/parsing.c \

OBJS		= $(SRCS:srcs/%.c=objs/%.o)

all:		$(NAME)

$(LIBFT):
		make -C libft

objs/%.o: srcs/%.c 
		mkdir -p $(@D)
		$(CC) $(CFLAGS) $(INCLUDES) -I/usr/include -Imlx_linux -O3 -c $< -o $@


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
