/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/12 16:30:48 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Every function used to display something on screen :
 *	
 *	unsigned int	get_pixel_from_img(t_img *img, int x, int y);
 *	void			my_mlx_pixel_put(t_img *img, int x, int y, 
 *									unsigned int pixel);
 *	void			draw_sprite(t_game *game, t_img *sprite, 
 *								int pos_x, int pos_y);
 *	int				rendering(t_game *game);
 */

/*
 *Calculate the position of a specific pixel from an xpm img and return it
 */
unsigned int	get_pixel_from_img(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bits_per_pixels / 8));
	return (*(unsigned int *)pixel);
}

/*
 * Put a pixel on an image (created before)
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int pixel)
{
	char	*dst;

	if (x >= WIDTH_WINDOW || y >= HEIGHT_WINDOW || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixels / 8));
	*(unsigned int *)dst = pixel;
}

/*
 * Draw a sprite (loaded before) at x and y positions in the buffer image
 */
void	draw_sprite(t_game *game, t_img *sprite, int pos_x, int pos_y)
{
	unsigned int	pixel;
	int				x;
	int				y;

	y = 0;
	while (y < sprite->height)
	{
		x = 0;
		while (x < sprite->width)
		{
			pixel = get_pixel_from_img(sprite, x, y);
			if (pixel != TRANSPARENT)
				my_mlx_pixel_put(&game->buffer, x + pos_x, y + pos_y, pixel);
			x++;
		}
		y++;
	}
}

void	draw_column(t_game *game, t_raycasting *ray, int x)
{
	unsigned int	wall_color;
	int				y;

	/* --- PLAFOND : du haut de l'écran jusqu'au début du mur --- */
	y = 0;
	while (y < ray->drawstart)
	{
		my_mlx_pixel_put(&game->buffer, x, y, CEILING_COLOR);
		y++;
	}
	/* --- MUR : de drawstart à drawend --- */
	if (ray->side == 0)
		wall_color = WALL_NS_COLOR; /* face E/W : plus claire */
	else
		wall_color = WALL_EW_COLOR; /* face N/S : plus sombre */
	while (y <= ray->drawend)
	{
		my_mlx_pixel_put(&game->buffer, x, y, wall_color);
		y++;
	}
	/* --- SOL : du bas du mur jusqu'en bas de l'écran --- */
	while (y < HEIGHT_WINDOW)
	{
		my_mlx_pixel_put(&game->buffer, x, y, FLOOR_COLOR);
		y++;
	}
}

/*
 * Rendering each frame (associate with mlx_loop_hook)
 */
int	rendering(t_game *game)
{
	ft_bzero(game->buffer.addr, (game->buffer.width * game->buffer.height) * 4);
	move_player(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->window,
		game->buffer.mlx_img, 0, 0);
	return (0);
}
