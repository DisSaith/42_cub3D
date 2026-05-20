/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:58:30 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/20 17:36:49 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 * Free and destroy parsing data
 */
void	free_parsing_data(t_game *game)
{
	int	i;

	if (game->file.file_content)
	{
		i = 0;
		while (game->file.file_content[i])
			free(game->file.file_content[i++]);
		free(game->file.file_content);
	}
	if (game->file.map)
	{
		i = 0;
		while (game->file.map[i])
			free(game->file.map[i++]);
		free(game->file.map);
	}
	if (game->textures.path_no)
		free(game->textures.path_no);
	if (game->textures.path_so)
		free(game->textures.path_so);
	if (game->textures.path_ea)
		free(game->textures.path_ea);
	if (game->textures.path_we)
		free(game->textures.path_we);
}

/*
 * Free and destroy mlx data
 */
void	free_mlx_data(t_game *game)
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
}

/*
 * Call all functions to free and clean data
 */
void	free_game_data(t_game *game)
{
	if (!game)
		return ;
	free_parsing_data(game);
	free_mlx_data(game);
}

/*
 *Free, destroy and close everything for no leaks before exit
 */
int	close_game(t_game *game)
{
	free_parsing_data(game);
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
