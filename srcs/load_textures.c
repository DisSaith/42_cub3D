/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/15 17:48:36 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Function needed to load xpm file before displaying it (rendering)
 *
 * int	load_buffer(t_game *game);
 * int	load_textures(t_game *game);
 * int	load_xpm(t_game *game, t_img *img, char *path);
 */

/*
 * Create and initialise image buffer
 */
int	load_buffer(t_game *game)
{
	game->buffer.mlx_img = mlx_new_image(game->mlx,
			WIDTH_WINDOW, HEIGHT_WINDOW);
	if (!game->buffer.mlx_img)
		return (0);
	game->buffer.addr = mlx_get_data_addr(game->buffer.mlx_img,
			&game->buffer.bits_per_pixels,
			&game->buffer.line_len,
			&game->buffer.endian);
	game->buffer.width = WIDTH_WINDOW;
	game->buffer.height = HEIGHT_WINDOW;
	return (1);
}

int	load_mini_map(t_game *game)
{
	game->file.map_height = 10;
	game->file.map_width = 10;
	game->mini_map.mlx_img = mlx_new_image(game->mlx,
			WIDTH_WINDOW / game->file.map_width, HEIGHT_WINDOW / game->file.map_height);
	if (!game->mini_map.mlx_img)
		return (0);
	game->mini_map.addr = mlx_get_data_addr(game->mini_map.mlx_img,
			&game->mini_map.bits_per_pixels,
			&game->mini_map.line_len,
			&game->mini_map.endian);
	game->mini_map.width = WIDTH_WINDOW / game->file.map_width;
	game->mini_map.height = HEIGHT_WINDOW / game->file.map_height;
	return (1);
}

/*
 * Load and initialise every texture for the game
 */
int	load_textures(t_game *game)
{
	if (!load_xpm(game, &game->textures.north, "textures/north.xpm"))
		return (0);
	if (!load_xpm(game, &game->textures.south, "textures/south.xpm"))
		return (0);
	if (!load_xpm(game, &game->textures.east, "textures/east.xpm"))
		return (0);
	if (!load_xpm(game, &game->textures.west, "textures/west.xpm"))
		return (0);
	return (1);
}

/*
 * Load an xpm file and initialise its data used by mlx
 */
int	load_xpm(t_game *game, t_img *img, char *path)
{
	img->mlx_img = mlx_xpm_file_to_image(game->mlx, path,
			&img->width, &img->height);
	if (!img->mlx_img)
		return (0);
	img->addr = mlx_get_data_addr(img->mlx_img,
			&img->bits_per_pixels,
			&img->line_len,
			&img->endian);
	return (1);
}
