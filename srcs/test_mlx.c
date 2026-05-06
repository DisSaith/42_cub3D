/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/06 16:41:34 by acohaut          ###   ########.fr       */
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

unsigned int	get_pixel_from_img(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bits_per_pixels / 8));
	return (*(unsigned int *)pixel);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int pixel)
{
	char	*dst;

	if (x >= WIDTH_WINDOW || y >= HEIGHT_WINDOW || x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bits_per_pixels / 8));
	*(unsigned int *)dst = pixel;
}

int	load_buffer(t_game *game)
{
	game->buffer.mlx_img = mlx_new_image(game->mlx, WIDTH_WINDOW, HEIGHT_WINDOW);
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

int	load_textures(t_game *game)
{
	if (!load_xpm(game, &game->wall, "textures/wall.xpm"))
		return (0);
	if (!load_xpm(game, &game->enemy, "textures/enemy.xpm"))
		return (0);
	game->wall.x = 50;
	game->wall.y = 50;
	return (1);
}

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

/*
 *Rendering each frame (associate with mlx_loop_hook)
 */
int	rendering(void)
{
	t_game	*game;
	int		x_line;
	int		y_line;
	int		vector_pw;

	game = get_game_ptr(NULL);
	x_line = game->wall.x + (game->wall.width / 2); 
	y_line = game->wall.y + (game->wall.height / 2);
	vector_pw = sqrt((game->player.x - x_line) * (game->player.x - x_line)
				+ (game->player.y - y_line) * (game->player.y - y_line));
	printf("vector_pw = %d\n", vector_pw);
	ft_bzero(game->buffer.addr, game->buffer.width * game->buffer.height * 4);
	//mlx_clear_window(game->mlx, game->window);
	//draw_background(game, BLUE);
	draw_sprite(game, &game->wall, game->wall.x, game->wall.y);
	draw_sprite(game, &game->enemy, 100, 100);
	draw_a_line(game, x_line, y_line);
	mlx_put_image_to_window(game->mlx, game->window, game->buffer.mlx_img, 0, 0);
	mlx_string_put(game->mlx, game->window,
		game->player.x, game->player.y, GREEN, "p");
	return (0);
}
