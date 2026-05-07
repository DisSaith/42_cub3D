/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/07 16:48:12 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Function needed to move player and catch key press/release :
 *
 * int	key_press(int keycode, t_game *game);
 * int	key_release(int keycode, t_game *game);
 * int	check_collision(t_game *game, float speed)
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
	return (0);
}

/*
 * Prevent collision with walls and map limits
 */
int	check_collision(t_game *game, float speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x;
	new_y = game->player.y;
	if (game->player.w_press == true)
		new_y -= speed;
	if (game->player.s_press == true)
		new_y += speed;
	if (game->player.d_press == true)
		new_x += speed;
	if (game->player.a_press == true)
		new_x -= speed;
	if (new_x < 0 || new_y < 0
		|| new_x > (double)WIDTH_WINDOW || new_y > (double)HEIGHT_WINDOW)
		return (0);
	return (1);
}

/*
 *Allow us to move the player after pressing the keyboard (W,S,D,A)
 */
void	move_player(t_game *game)
{
	double	speed;

	speed = 0.5;
	if (!check_collision(game, speed))
		return ;
	if (game->player.w_press == true)
	{
		game->player.y -= speed;
		game->player.direction = 'N';
	}
	if (game->player.s_press == true)
	{
		game->player.y += speed;
		game->player.direction = 'S';
	}
	if (game->player.d_press == true)
	{
		game->player.x += speed;
		game->player.direction = 'E';
	}
	if (game->player.a_press == true)
	{
		game->player.x -= speed;
		game->player.direction = 'W';
	}
}
