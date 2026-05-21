/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:58:30 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/21 11:03:45 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 * Free and destroy mlx data
 */
void	free_mlx_data_b(t_game *game)
{
	if (game->buffer.mlx_img)
		mlx_destroy_image(game->mlx, game->buffer.mlx_img);
	if (game->mini_map.img.mlx_img)
		mlx_destroy_image(game->mlx, game->mini_map.img.mlx_img);
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
}

/*
 * Call all functions to free and clean data
 */
void	free_game_data_b(t_game *game)
{
	if (!game)
		return ;
	free_parsing_data(game);
	free_mlx_data_b(game);
}

/*
 *Free, destroy and close everything for no leaks before exit
 */
int	close_game_b(t_game *game)
{
	free_parsing_data(game);
	if (game->buffer.mlx_img)
		mlx_destroy_image(game->mlx, game->buffer.mlx_img);
	if (game->mini_map.img.mlx_img)
		mlx_destroy_image(game->mlx, game->mini_map.img.mlx_img);
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
 * Free all data and display error message
 */
void	error_exit_b(char *error_message)
{
	size_t	n;

	free_game_data_b(get_game_ptr(NULL));
	n = ft_strlen(error_message);
	write(2, "Error\n", 7);
	write(2, error_message, n);
	write(2, "\n", 1);
	exit(1);
}
