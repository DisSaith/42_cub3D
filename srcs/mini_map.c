/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/15 16:46:53 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Every function used to display something on screen :
 *	
 *	void			my_mlx_pixel_put(t_img *img, int x, int y, 
 *									unsigned int pixel);
 *	void			draw_sprite(t_game *game, t_img *sprite, 
 *								int pos_x, int pos_y);
 *	void			draw_column(t_game *game, t_raycasting *ray, int x);
 *	void			raycasting(t_game *game)
 *	int				rendering(t_game *game);
 */

/*
 * Draw a sprite (loaded before) at x and y positions in the buffer image
 */
void	draw_mini_map(t_game *game, t_img *sprite, int pos_x, int pos_y)
{
	unsigned int	pixel;
	int				x;
	int				y;

	y = 0;
	while (y < game->file.map_height && y < sprite->height)
	{
		x = 0;
		while (y < game->file.map_width && x < sprite->width)
		{
			if (game->file.map[y][x] == '1')
				my_mlx_pixel_put(&game->buffer, x + pos_x, y + pos_y, RED);
			else
				my_mlx_pixel_put(&game->buffer, x + pos_x, y + pos_y, BLUE);
			x++;
		}
		y++;
	}
}
