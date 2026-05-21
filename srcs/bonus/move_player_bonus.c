/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/21 11:42:10 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Function needed to move player :
 *
 * void	rotate_left_b(t_game *game, double rotation,
 *						double old_dir_x, double old_plan_x);
 * void	rotate_right_b(t_game *game, double rotation,
 *						double old_dir_x, double old_plan_x);
 * void	rotate_fov_b(t_game *game, double rotation,
 *						double old_dir_x, double old_plan_x);
 * void	move_player_b(t_game *game);
 */

/*
 * Left rotation if mouse move on left
 */
void	rotate_left_b(t_game *game, double rotation,
			double old_dir_x, double old_plan_x)
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

/*
 * Right rotation if mouse move on right
 */
void	rotate_right_b(t_game *game, double rotation,
			double old_dir_x, double old_plan_x)
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

/*
 * Horizontal rotation if LEFT or RIGHT key are pressed
 */
void	rotate_fov_b(t_game *game, double rotation,
			double old_dir_x, double old_plan_x)
{
	double	delta_x;
	int		new_mouse_x;

	mlx_mouse_get_pos(game->mlx, game->window,
		&new_mouse_x, &game->player.mouse_y);
	delta_x = new_mouse_x - game->player.mouse_x;
	if (delta_x < 0 && game->player.shift_r_press == false)
		rotate_left_b(game, rotation, old_dir_x, old_plan_x);
	else if (delta_x > 0 && game->player.shift_r_press == false)
		rotate_right_b(game, rotation, old_dir_x, old_plan_x);
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
	rotation = 0.08;
	rotate_fov_b(game, rotation, game->player.dir_x, game->player.plan_x);
	move_vertical(game, speed);
	move_horizontal(game, speed);
}
