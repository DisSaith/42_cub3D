/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/07 13:22:18 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 *File where i test some stuff with mlx library for better understanding
 */

/*
 *Fonction to draw a line between a point and the player position
 */
void	draw_a_line(t_game *game, int x, int y)
{
	double			delta_x;
	double			delta_y;
	double			pixel_x;
	double			pixel_y;
	unsigned int	pixels;

	delta_x = x - game->player.x;
	delta_y = y - game->player.y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	pixel_x = game->player.x;
	pixel_y = game->player.y;
	delta_x /= pixels;
	delta_y /= pixels;
	while (pixels > 0)
	{
		my_mlx_pixel_put(&game->buffer, pixel_x, pixel_y, RED);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

void	draw_background(t_game *game, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT_WINDOW)
	{
		x = 0;
		while (x < WIDTH_WINDOW)
		{
			my_mlx_pixel_put(&game->buffer, x, y, color);
			x++;
		}
		y++;
	}
}
