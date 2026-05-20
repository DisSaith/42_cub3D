/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/20 14:57:20 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 *Initialize player struct position and direction
 */
void	init_player(t_game *game)
{
	game->player.w_press = false;
	game->player.s_press = false;
	game->player.d_press = false;
	game->player.a_press = false;
	game->player.right_press = false;
	game->player.left_press = false;
}

/*
 *Initialize game struct and mlx struct for start the game
 */
int	initialisation_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		error_exit("mlx init");
	game->window = mlx_new_window(game->mlx,
			WIDTH_WINDOW, HEIGHT_WINDOW, "cub3D");
	if (!game->window)
		error_exit("mlx window");
	if (!load_img(game, &game->buffer, WIDTH_WINDOW, HEIGHT_WINDOW))
		error_exit("loading buffer");
	if (!load_textures(game))
		error_exit("loading textures");
	init_player(game);
	return (1);
}
