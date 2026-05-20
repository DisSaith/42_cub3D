/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/20 14:58:28 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Function needed to load xpm file before displaying it (rendering)
 *
 * int	load_img(t_game *game, t_img *img, int width, int height);
 * int	load_textures(t_game *game);
 * int	load_xpm(t_game *game, t_img *img, char *path);
 */

/*
 * Create and initialise a mlx image
 */
int	load_img(t_game *game, t_img *img, int width, int height)
{
	img->width = width;
	img->height = height;
	img->mlx_img = mlx_new_image(game->mlx, img->width, img->height);
	if (!img->mlx_img)
		return (0);
	img->addr = mlx_get_data_addr(img->mlx_img,
			&img->bits_per_pixels,
			&img->line_len,
			&img->endian);
	return (1);
}

/*
 * Load and initialise every texture for the game
 */
int	load_textures(t_game *game)
{
	if (!load_xpm(game, &game->textures.north, game->textures.path_no))
	{
		printf("Error\nloading texture NO: %s\n", game->textures.path_no);
		return (0);
	}
	if (!load_xpm(game, &game->textures.south, game->textures.path_so))
	{
		printf("Error\nloading texture SO: %s\n", game->textures.path_so);
		return (0);
	}
	if (!load_xpm(game, &game->textures.east, game->textures.path_ea))
	{
		printf("Error\nloading texture EA: %s\n", game->textures.path_ea);
		return (0);
	}
	if (!load_xpm(game, &game->textures.west, game->textures.path_we))
	{
		printf("Error\nloading texture WE: %s\n", game->textures.path_we);
		return (0);
	}
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
