/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/12 16:25:37 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Function needed to move player and catch key press/release :
 *
 * int	key_press(int keycode, t_game *game);
 * int	key_release(int keycode, t_game *game);
 * int	check_collision_x(t_game *game, double dx)
 * int	check_collision_y(t_game *game, double dy)
 * void	move_player(t_game *game);
 */

/*
 *Capture every press on the keyboard (ESC, W, S, D, A)
 */
int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		close_game(game);
	if (keycode == W_KEY)
		game->player.w_press = true;
	if (keycode == S_KEY)
		game->player.s_press = true;
	if (keycode == D_KEY)
		game->player.d_press = true;
	if (keycode == A_KEY)
		game->player.a_press = true;
	if (keycode == RIGHT_KEY)
		game->player.right_press = true;
	if (keycode == LEFT_KEY)
		game->player.left_press = true;
	return (0);
}

/*
 *Capture every release on the keyboard (W, S, D, A)
 */
int	key_release(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->player.w_press = false;
	if (keycode == S_KEY)
		game->player.s_press = false;
	if (keycode == D_KEY)
		game->player.d_press = false;
	if (keycode == A_KEY)
		game->player.a_press = false;
	if (keycode == RIGHT_KEY)
		game->player.right_press = false;
	if (keycode == LEFT_KEY)
		game->player.left_press = false;
	return (0);
}

int	check_collision_x(t_game *game, double dx)
{
	double	new_x = game->player.pos_x + dx;
	return (game->map.map[(int)(game->player.pos_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == 0);
}

int	check_collision_y(t_game *game, double dy)
{
	double	new_y = game->player.pos_y + dy;
	return (game->map.map[(int)(new_y / TILE_SIZE)][(int)(game->player.pos_x / TILE_SIZE)] == 0);
}

/*
 *Allow us to move the player after pressing the keyboard (W,S,D,A)
 * 3D moves with left and right POV rotation
 */
void	move_player(t_game *game)
{
	double	speed;
	double	rot;       // angle de rotation par frame
	double	old_dir_x;
	double	old_plan_x;

	speed = 1.0;       // en pixels par frame (pos est en pixels)
	rot   = 0.01;      // radians par frame (~2.3°)

	// --- ROTATION : flèches gauche / droite --- 
	if (game->player.left_press)
	{
		// Rotation dans le sens trigonométrique (angle négatif)
		old_dir_x  = game->player.dir_x;
		game->player.dir_x  = game->player.dir_x  * cos(-rot) - game->player.dir_y  * sin(-rot);
		game->player.dir_y  = old_dir_x            * sin(-rot) + game->player.dir_y  * cos(-rot);
		old_plan_x = game->player.plan_x;
		game->player.plan_x = game->player.plan_x  * cos(-rot) - game->player.plan_y * sin(-rot);
		game->player.plan_y = old_plan_x            * sin(-rot) + game->player.plan_y * cos(-rot);
	}
	if (game->player.right_press)
	{
		// Rotation dans le sens horaire (angle positif)
		old_dir_x  = game->player.dir_x;
		game->player.dir_x  = game->player.dir_x  * cos(rot)  - game->player.dir_y  * sin(rot);
		game->player.dir_y  = old_dir_x            * sin(rot)  + game->player.dir_y  * cos(rot);
		old_plan_x = game->player.plan_x;
		game->player.plan_x = game->player.plan_x  * cos(rot)  - game->player.plan_y * sin(rot);
		game->player.plan_y = old_plan_x            * sin(rot)  + game->player.plan_y * cos(rot);
	}

	// --- DÉPLACEMENT : W/S avance/recule dans la direction du regard --- 
	if (game->player.w_press)
	{
		if (check_collision_x(game,  game->player.dir_x * speed))
			game->player.pos_x += game->player.dir_x * speed;
		if (check_collision_y(game,  game->player.dir_y * speed))
			game->player.pos_y += game->player.dir_y * speed;
	}
	if (game->player.s_press)
	{
		if (check_collision_x(game, -game->player.dir_x * speed))
			game->player.pos_x -= game->player.dir_x * speed;
		if (check_collision_y(game, -game->player.dir_y * speed))
			game->player.pos_y -= game->player.dir_y * speed;
	}

	//--- STRAFE : A/D déplace latéralement (perpendiculaire au regard) --- 
	if (game->player.d_press)
	{
		if (check_collision_x(game,  game->player.plan_x * speed))
			game->player.pos_x += game->player.plan_x * speed;
		if (check_collision_y(game,  game->player.plan_y * speed))
			game->player.pos_y += game->player.plan_y * speed;
	}
	if (game->player.a_press)
	{
		if (check_collision_x(game, -game->player.plan_x * speed))
			game->player.pos_x -= game->player.plan_x * speed;
		if (check_collision_y(game, -game->player.plan_y * speed))
			game->player.pos_y -= game->player.plan_y * speed;
	}
}
