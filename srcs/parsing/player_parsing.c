/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:09:25 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/20 11:08:01 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_player_position(t_game *game, size_t x, size_t y)
{
	game->player.cardinal_point = game->file.map[y][x];
	game->player.pos_x = (x * TILE_SIZE) + (TILE_SIZE / 2);
	game->player.pos_y = (y * TILE_SIZE) + (TILE_SIZE / 2);
	init_player_vector(game, game->player.cardinal_point);
}

void	init_player_vector(t_game *game, char direction)
{
	if (direction == 'N')
	{
		game->player.dir_y = -1;
		game->player.plan_x = 0.66;
	}
	else if (direction == 'S')
	{
		game->player.dir_y = 1;
		game->player.plan_x = -0.66;
	}
	else if (direction == 'E')
	{
		game->player.dir_x = 1;
		game->player.plan_y = 0.66;
	}
	else if (direction == 'W')
	{
		game->player.dir_x = -1;
		game->player.plan_y = -0.66;
	}
}
