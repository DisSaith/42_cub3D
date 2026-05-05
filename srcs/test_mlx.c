/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/05 17:24:09 by acohaut          ###   ########.fr       */
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

	delta_x = x - game->x_player;
	delta_y = y - game->y_player;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	pixel_x = game->x_player;
	pixel_y = game->y_player;
	delta_x /= pixels;
	delta_y /= pixels;
	while (pixels > 0)
	{
		my_mlx_pixel_put(&game->img, pixel_x, pixel_y, RED);
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
			my_mlx_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixels / 8));
	*(unsigned int *)dst = color;
}

int	load_buffer(t_game *game)
{
	game->img.mlx_img = mlx_new_image(game->mlx, WIDTH_WINDOW, HEIGHT_WINDOW);
	game->img.addr = mlx_get_data_addr(game->img.mlx_img,
			&game->img.bits_per_pixels,
			&game->img.line_len,
			&game->img.endian);
	return (1);
}

/*
 *Rendering each frame (associate with mlx_loop_hook)
 */
int	rendering(void)
{
	t_game	*game;

	game = get_game_ptr(NULL);
	mlx_clear_window(game->mlx, game->window);
	draw_background(game, BLUE);
	draw_a_line(game, 45, 100);
	mlx_put_image_to_window(game->mlx, game->window, game->img.mlx_img, 0, 0);
	mlx_string_put(game->mlx, game->window,
		game->x_player, game->y_player, GREEN, "p");
	return (0);
}
