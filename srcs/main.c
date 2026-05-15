/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/15 15:14:03 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *Free, destroy and close everything for no leaks before exit
 */
int	close_game(t_game *game)
{
	if (game->buffer.mlx_img)
		mlx_destroy_image(game->mlx, game->buffer.mlx_img);
	if (game->textures.north.mlx_img)
		mlx_destroy_image(game->mlx, game->textures.north.mlx_img);
	if (game->textures.south.mlx_img)
		mlx_destroy_image(game->mlx, game->textures.south.mlx_img);
	if (game->textures.west.mlx_img)
		mlx_destroy_image(game->mlx, game->textures.west.mlx_img);
	if (game->textures.east.mlx_img)
		mlx_destroy_image(game->mlx, game->textures.east.mlx_img);
	if (game->window)
	{
		mlx_destroy_window(game->mlx, game->window);
		game->window = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}

/*
 *Initialize player struct position and direction
 */
void	init_player(t_game *game)
{
	game->player.pos_x = 15 * 64;
	game->player.pos_y = 10 * 64;
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->player.plan_x = 0.66;
	game->player.plan_y = 0;
	game->player.angle = PI / 2;
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
		return (0);
	game->window = mlx_new_window(game->mlx,
			WIDTH_WINDOW, HEIGHT_WINDOW, "cub3D");
	if (!game->window)
		return (0);
	if (!load_buffer(game))
		return (0);
	if (!load_textures(game))
		return (0);
	init_player(game);
	game->cur_time = 0;
	game->old_time = 0;
	return (1);
}

/*
 *Main function of the program
 */
int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	check_file(&game.file, argc, argv[1]);
	for (size_t y = 0 ; game.file.map[y] != NULL ; y++)
			printf("%s", game.file.map[y]);
	get_game_ptr(&game);
	if (!initialisation_game(&game))
		close_game(&game);
	mlx_hook(game.window, 2, 1 << 0, (int (*)())(void *)key_press, &game);
	mlx_hook(game.window, 3, 1 << 1, (int (*)())(void *)key_release, &game);
	mlx_hook(game.window, 17, 1 << 0, (int (*)())(void *)close_game, &game);
	mlx_loop_hook(game.mlx, (int (*)())(void *)rendering, &game);
	mlx_loop(game.mlx);
	return (0);
}
