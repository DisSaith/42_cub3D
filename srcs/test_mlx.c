/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/14 17:58:58 by acohaut          ###   ########.fr       */
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

	delta_x = x - game->player.pos_x;
	delta_y = y - game->player.pos_y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	pixel_x = game->player.pos_x;
	pixel_y = game->player.pos_y;
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

int	touch(t_game *game, double x, double y)
{
	if (game->file.map[(int)y / 64][(int)x / 64] == '1')
		return (1);
	return (0);
}

void	move_player_2d(t_game *game)
{
	double	speed;
	double	angle_speed;
	double	cos_angle;
	double	sin_angle;

	cos_angle = cos(game->player.angle);
	sin_angle = sin(game->player.angle);
	speed = 0.5;
	angle_speed = 0.02;
	if (!check_collision_2d(game, speed))
		return ;
	if (game->player.left_press)
		game->player.angle -= angle_speed;
	if (game->player.right_press)
		game->player.angle += angle_speed;
	if (game->player.angle > 2 * PI)
		game->player.angle = 0;
	if (game->player.angle < 0)
		game->player.angle = 2 * PI;
	if (game->player.w_press == true)
	{
		game->player.pos_y -= speed;
		game->player.dir_y = -1;
	}
	if (game->player.s_press == true)
	{
		game->player.pos_y += speed;
		game->player.dir_y = 1;
	}
	if (game->player.d_press == true)
	{
		game->player.pos_x += speed;
		game->player.dir_x = 1;
	}
	if (game->player.a_press == true)
	{
		game->player.pos_x -= speed;
		game->player.dir_x = -1;
	}
}

/*
 * Prevent collision with walls and map limits
 */
int	check_collision_2d(t_game *game, float speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x;
	new_y = game->player.pos_y;
	if (game->player.w_press == true)
		new_y -= speed;
	if (game->player.s_press == true)
		new_y += speed;
	if (game->player.d_press == true)
		new_x += speed;
	if (game->player.a_press == true)
		new_x -= speed;
	if (new_x < 0 || new_y < 0
		|| new_x > (double)WIDTH_WINDOW || new_y > (double)HEIGHT_WINDOW
		|| game->file.map[(int)new_y / 64][(int)new_x / 64] == '1')
		return (0);
	return (1);
}

/*
 *Allow us to move the player after pressing the keyboard (W,S,D,A)
 * 2D moves
 */
int	rendering_2d(t_game *game)
{
	double	ray_x = game->player.pos_x;
	double	ray_y = game->player.pos_y;
	double	cos_angle = cos(game->player.angle);
	double	sin_angle = sin(game->player.angle);
	double	x_line;
	double	y_line;
	double	vector_pw;

	x_line = 50 + (game->wall.width / 2);
	y_line = 50 + (game->wall.height / 2);
	vector_pw = sqrt((game->player.pos_x - x_line) * (game->player.pos_x - x_line)
			+ (game->player.pos_y - y_line) * (game->player.pos_y - y_line));
	//printf("vector_pw = %f\n", vector_pw);
	ft_bzero(game->buffer.addr, (game->buffer.width * game->buffer.height) * 4);
	draw_background(game, BLUE);
	/*for(size_t y = 0 ; y < game->map.height ; y++)
	{
		for(size_t x = 0 ; x < game->map.width ; x++)
		{
			if (game->file.map[y][x] == '1')
				draw_sprite(game, &game->wall, x * 64, y * 64);
		}
	}*/
	while (!touch(game, ray_x, ray_y))
	{
		my_mlx_pixel_put(&game->buffer, ray_x, ray_y, RED);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	draw_sprite(game, &game->enemy, 100, 100);
	move_player_2d(game);
	mlx_put_image_to_window(game->mlx, game->window,
		game->buffer.mlx_img, 0, 0);
	mlx_string_put(game->mlx, game->window,
		game->player.pos_x, game->player.pos_y, GREEN, "p");
	return (0);
}
