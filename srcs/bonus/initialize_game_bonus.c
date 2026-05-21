/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/21 11:23:21 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 *Initialize player struct position and direction
 */
void	init_player_b(t_game *game)
{
	mlx_mouse_get_pos(game->mlx, game->window,
		&game->player.mouse_x, &game->player.mouse_y);
	game->player.w_press = false;
	game->player.s_press = false;
	game->player.d_press = false;
	game->player.a_press = false;
	game->player.right_press = false;
	game->player.left_press = false;
	game->player.shift_r_press = false;
}

/*
 *Initialize game struct and mlx struct for start the game
 */
int	initialisation_game_b(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit_b("mlx init");
	game->window = mlx_new_window(game->mlx,
			WIDTH_WINDOW, HEIGHT_WINDOW, "cub3D");
	if (!game->window)
		error_exit_b("mlx window");
	mlx_mouse_hide(game->mlx, game->window);
	if (!load_img(game, &game->buffer, WIDTH_WINDOW, HEIGHT_WINDOW))
		error_exit_b("loading buffer");
	if (!load_img(game, &game->mini_map.img, 160, 160))
		error_exit_b("loading minimap");
	if (!load_textures(game))
		error_exit_b("loading textures");
	init_player_b(game);
	return (1);
}
