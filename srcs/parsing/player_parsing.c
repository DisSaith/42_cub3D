/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:09:25 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/19 15:09:29 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_player_position(t_game *game, size_t x, size_t y)
{
	game->player.cardinal_point = game->file.map[y][x];
	game->player.pos_x = x * TILE_SIZE;
	game->player.pos_y = y * TILE_SIZE;
}
