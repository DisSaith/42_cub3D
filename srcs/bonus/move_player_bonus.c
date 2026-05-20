/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/20 17:25:46 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Function needed to move player :
 *
 * void	move_player_b(t_game *game);
 */

/*
 * Horizontal rotation if LEFT or RIGHT key are pressed
 */
void	rotate_fov_b(t_game *game, double rotation)
{
	double	old_dir_x;
	double	old_plan_x;
	double	delta_x;
	int		new_mouse_x;

	mlx_mouse_get_pos(game->mlx, game->window, &new_mouse_x, &game->player.mouse_y);
	delta_x = new_mouse_x - game->player.mouse_x;
	old_dir_x = game->player.dir_x;
	old_plan_x = game->player.plan_x;
	if (delta_x < 0 && game->player.shift_r_press == false)
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
	else if (delta_x > 0 && game->player.shift_r_press == false)
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
	if (game->player.shift_r_press == false)
		mlx_mouse_move(game->mlx, game->window, WIDTH_WINDOW/2, HEIGHT_WINDOW/2);
}

/*
 *Allow us to move the player after pressing the keyboard (W,S,D,A)
 * 3D moves and left and right FOV rotation (left and right key)
 */
void	move_player_b(t_game *game)
{
	double	speed;
	double	rotation;

	speed = 5.0;
	rotation = 0.05;
	rotate_fov_b(game, rotation);
	//rotate_fov(game, rotation, game->player.dir_x, game->player.plan_x);
	move_vertical(game, speed);
	move_horizontal(game, speed);
}
