/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/21 11:37:44 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Every function used to display something on screen :
 *	
 *	void			my_mlx_pixel_put(t_img *img, int x, int y, 
 *									unsigned int pixel);
 *	void			draw_column(t_game *game, t_raycasting *ray, int x);
 *	void			raycasting_b(t_game *game)
 *	int				rendering_b(t_game *game);
 */

/*
 * Put a pixel on an image (created before)
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int pixel)
{
	char	*dst;

	if (x >= img->width || y >= img->height || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixels / 8));
	*(unsigned int *)dst = pixel;
}

/*
 *	Draw a column and determine the ceiling, floor and wall texture to draw
 */
void	draw_column(t_game *game, t_raycasting *ray, t_column *column, int x)
{
	int	y;

	column->step = (double)TILE_SIZE / ray->lineheight;
	column->tex_pos = (ray->drawstart - HEIGHT_WINDOW / 2 + ray->lineheight / 2)
		* column->step;
	y = 0;
	while (y < ray->drawstart)
	{
		my_mlx_pixel_put(&game->buffer, x, y, game->textures.ceiling);
		y++;
	}
	while (y <= ray->drawend)
	{
		column->tex_y = (int)column->tex_pos & (TILE_SIZE - 1);
		my_mlx_pixel_put(&game->buffer, x, y,
			get_pixel_from_img(column->texture, column->tex_x, column->tex_y));
		column->tex_pos += column->step;
		y++;
	}
	while (y < HEIGHT_WINDOW)
	{
		my_mlx_pixel_put(&game->buffer, x, y, game->textures.floor);
		y++;
	}
}

/*
 * Perform raycasting :
 * Cast a ray in each column of the FOV player and calculate the distance
 * between the player and walls to determine what to display in 3D
 */
void	raycasting_b(t_game *game)
{
	t_raycasting	ray;
	t_column		column;
	t_mini_map		*mini_map;

	ray.x = 0;
	mini_map = &game->mini_map;
	while (ray.x < WIDTH_WINDOW)
	{
		initialize_ray1(game, &ray);
		initialize_ray2(&ray);
		perform_dda_algorithme(game, &ray);
		calculate_what_to_display_b(game, &ray, &column, mini_map);
		draw_line_minimap(game);
		draw_column(game, &ray, &column, ray.x);
		ray.x++;
	}
}

/*
 * Rendering each frame (associate with mlx_loop_hook)
 */
int	rendering_b(t_game *game)
{
	if (game->player.shift_r_press == false)
		mlx_mouse_move(game->mlx, game->window,
			WIDTH_WINDOW / 2, HEIGHT_WINDOW / 2);
	mlx_mouse_get_pos(game->mlx, game->window,
		&game->player.mouse_x, &game->player.mouse_y);
	ft_bzero(game->buffer.addr,
		game->buffer.line_len * game->buffer.height);
	ft_bzero(game->mini_map.img.addr,
		game->mini_map.img.line_len * game->mini_map.img.height);
	move_player_b(game);
	draw_minimap(game);
	raycasting_b(game);
	mlx_put_image_to_window(game->mlx, game->window,
		game->buffer.mlx_img, 0, 0);
	mlx_put_image_to_window(game->mlx, game->window,
		game->mini_map.img.mlx_img, 10, 10);
	return (0);
}
