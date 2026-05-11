/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/11 12:12:15 by acohaut          ###   ########.fr       */
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

/*
 * Rendering each frame (associate with mlx_loop_hook)
 */
int	rendering(t_game *game)
{
	int		x_line;
	int		y_line;
	//double	vector_pw;

	x_line = game->wall.x + (game->wall.width / 2);
	y_line = game->wall.y + (game->wall.height / 2);
	//vector_pw = sqrt((game->player.x - x_line) * (game->player.x - x_line)
	//		+ (game->player.y - y_line) * (game->player.y - y_line));
	//printf("vector_pw = %f\n", vector_pw);
	ft_bzero(game->buffer.addr, (game->buffer.width * game->buffer.height) * 4);
	draw_background(game, BLUE);
	move_player(game);
	for(size_t y = 0 ; y < game->map.height ; y++)
	{
		for(size_t x = 0 ; x < game->map.width ; x++)
		{
			if (game->map.map[y][x] == 1)
				draw_sprite(game, &game->wall, x * 64, y * 64);
		}
	}
	//draw_sprite(game, &game->wall, game->wall.x, game->wall.y);
	draw_sprite(game, &game->enemy, 100, 100);
	draw_a_line(game, x_line, y_line);
	mlx_put_image_to_window(game->mlx, game->window,
		game->buffer.mlx_img, 0, 0);
	mlx_string_put(game->mlx, game->window,
		game->player.pos_x, game->player.pos_y, GREEN, "p");
	return (0);
}
