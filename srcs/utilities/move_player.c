/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/20 12:42:01 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Function needed to move player :
 *
 * int	check_collision(t_game *game, char direction,
 *						double dir_x, double dir_y);
 * void	rotate_fov(t_game *game, double rotation,
 *					double old_dir_x, double old_plan_x);
 * void	move_vertical(t_game *game, double speed);
 * void	move_horizontal(t_game *game, double speed);
 * void	move_player(t_game *game);
 */

/*
 * Check collision in y or x with a wall
 */
int	check_collision(t_game *game, char direction, double dir_x, double dir_y)
{
	int	new_y;
	int	new_x;
	int	x;
	int	y;

	if (direction == 'x')
	{
		new_x = (game->player.pos_x + dir_x) / TILE_SIZE;
		y = game->player.pos_y / TILE_SIZE;
		if (game->file.map[y][new_x] == '1')
			return (0);
	}
	if (direction == 'y')
	{
		new_y = (game->player.pos_y + dir_y) / TILE_SIZE;
		x = game->player.pos_x / TILE_SIZE;
		if (game->file.map[new_y][x] == '1')
			return (0);
	}
	return (1);
}

/*
 * Horizontal rotation if LEFT or RIGHT key are pressed
 */
void	rotate_fov(t_game *game, double rotation,
			double old_dir_x, double old_plan_x)
{
	if (game->player.left_press == true)
	{
		game->player.dir_x = old_dir_x * cos(-rotation)
			- game->player.dir_y * sin(-rotation);
		game->player.dir_y = old_dir_x * sin(-rotation)
			+ game->player.dir_y * cos(-rotation);
		game->player.plan_x = old_plan_x * cos(-rotation)
			- game->player.plan_y * sin(-rotation);
		game->player.plan_y = old_plan_x * sin(-rotation)
			+ game->player.plan_y * cos(-rotation);
	}
	else if (game->player.right_press == true)
	{
		game->player.dir_x = old_dir_x * cos(rotation)
			- game->player.dir_y * sin(rotation);
		game->player.dir_y = old_dir_x * sin(rotation)
			+ game->player.dir_y * cos(rotation);
		game->player.plan_x = old_plan_x * cos(rotation)
			- game->player.plan_y * sin(rotation);
		game->player.plan_y = old_plan_x * sin(rotation)
			+ game->player.plan_y * cos(rotation);
	}
}

/*
 * Vertical movement if W or S key are pressed
 */
void	move_vertical(t_game *game, double speed)
{
	if (game->player.w_press == true)
	{
		if (check_collision(game, 'x', game->player.dir_x * speed, 0))
			game->player.pos_x += game->player.dir_x * speed;
		if (check_collision(game, 'y', 0, game->player.dir_y * speed))
			game->player.pos_y += game->player.dir_y * speed;
	}
	if (game->player.s_press == true)
	{
		if (check_collision(game, 'x', -game->player.dir_x * speed, 0))
			game->player.pos_x -= game->player.dir_x * speed;
		if (check_collision(game, 'y', 0, -game->player.dir_y * speed))
			game->player.pos_y -= game->player.dir_y * speed;
	}
}

/*
 * Horizontal movement if D or A key are pressed
 */
void	move_horizontal(t_game *game, double speed)
{
	if (game->player.d_press == true)
	{
		if (check_collision(game, 'x', game->player.plan_x * speed, 0))
			game->player.pos_x += game->player.plan_x * speed;
		if (check_collision(game, 'y', 0, game->player.plan_y * speed))
			game->player.pos_y += game->player.plan_y * speed;
	}
	if (game->player.a_press == true)
	{
		if (check_collision(game, 'x', -game->player.plan_x * speed, 0))
			game->player.pos_x -= game->player.plan_x * speed;
		if (check_collision(game, 'y', 0, -game->player.plan_y * speed))
			game->player.pos_y -= game->player.plan_y * speed;
	}
}

/*
 *Allow us to move the player after pressing the keyboard (W,S,D,A)
 * 3D moves and left and right FOV rotation (left and right key)
 */
void	move_player(t_game *game)
{
	double	speed;
	double	rotation;

	speed = 5.0;
	rotation = 0.05;
	rotate_fov(game, rotation, game->player.dir_x, game->player.plan_x);
	move_vertical(game, speed);
	move_horizontal(game, speed);
}
