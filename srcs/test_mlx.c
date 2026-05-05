/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/04 18:09:08 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	draw_a_line(t_game *game, int x, int y)
{
	while (x != game->x_player && y != game->y_player)
	{
		mlx_pixel_put(game->mlx, game->window, x, y, 0x00FF0000);
		if (x > game->x_player)
			x--;
		else if (x < game->x_player)
			x++;
		if (y > game->y_player)
			y--;
		else if (y < game->y_player)
			y++;
	}
	return (1);
}
