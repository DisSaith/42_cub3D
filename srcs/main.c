/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/06 15:40:22 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_game *game)
{
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

int	initialisation_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->window = mlx_new_window(game->mlx, 480, 480, "cub3D");
	if (!game->window)
		return (0);
	game->x_player = 60;
	game->y_player = 65;
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;
	void	*img;
	int		w;
	int		h;

	ft_memset(&game, 0, sizeof(t_game));
	check_map(argc, argv[1]);
	get_game_ptr(&game);
	if (!initialisation_game(&game))
		close_game(&game);
	img = mlx_xpm_file_to_image(game.mlx, "textures/wall.xpm", &w, &h);
	mlx_put_image_to_window(game.mlx, game.window, img, 100, 100);
	draw_a_line(&game, 45, 100);
	mlx_key_hook(game.window, &handle_key, &game);
	mlx_loop(game.mlx);
	return (0);
}
