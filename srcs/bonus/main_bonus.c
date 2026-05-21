/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/21 11:22:47 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *Main function of the program
 */
int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	get_game_ptr(&game);
	game.file.game = &game;
	check_file(&game.file, &game.textures, argc, argv[1]);
	initialisation_game_b(&game);
	mlx_hook(game.window, 2, 1 << 0, (int (*)())(void *)key_press_b, &game);
	mlx_hook(game.window, 3, 1 << 1, (int (*)())(void *)key_release_b, &game);
	mlx_hook(game.window, 17, 1 << 0, (int (*)())(void *)close_game_b, &game);
	mlx_loop_hook(game.mlx, (int (*)())(void *)rendering_b, &game);
	mlx_loop(game.mlx);
	return (0);
}
