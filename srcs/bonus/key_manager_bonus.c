/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_manager_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/21 11:00:22 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Function needed to catch key press/release :
 *
 * int	key_press_b(int keycode, t_game *game);
 * int	key_release_b(int keycode, t_game *game);
 */

/*
 *Capture every press on the keyboard (ESC, W, S, D, A)
 */
int	key_press_b(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		close_game_b(game);
	if (keycode == SHIFT_R_KEY)
	{
		mlx_mouse_show(game->mlx, game->window);
		game->player.shift_r_press = true;
	}
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
int	key_release_b(int keycode, t_game *game)
{
	if (keycode == SHIFT_R_KEY)
	{
		mlx_mouse_hide(game->mlx, game->window);
		game->player.shift_r_press = false;
	}
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
