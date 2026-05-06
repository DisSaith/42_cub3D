/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/06 15:45:51 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *Store and return the pointer of the main structure game with all data
 */
t_game	*get_game_ptr(t_game *ptr)
{
	static t_game	*game;

	if (ptr)
		game = ptr;
	return (game);
}

/*
 *Allow us to move the player after pressing the keyboard (W,S,D,A)
 */
void	move_player(t_game *game, int dir_x, int dir_y, char direction)
{
	int	new_x;
	int	new_y;

	game->player.direction = direction;
	new_x = (game->player.x / TILE_SIZE) + dir_x;
	new_y = (game->player.y / TILE_SIZE) + dir_y;
	game->player.x = new_x * TILE_SIZE;
	game->player.y = new_y * TILE_SIZE;
}

/*
 *Capture every press on the keyboard and execute the relevant function
 */
int	handle_key(int keycode, void *s_game_ptr)
{
	if (keycode == ESC_KEY)
		close_game(s_game_ptr);
	else if (keycode == W_KEY)
		move_player(s_game_ptr, 0, -1, 'N');
	else if (keycode == S_KEY)
		move_player(s_game_ptr, 0, 1, 'S');
	else if (keycode == D_KEY)
		move_player(s_game_ptr, 1, 0, 'E');
	else if (keycode == A_KEY)
		move_player(s_game_ptr, -1, 0, 'W');
	return (0);
}
