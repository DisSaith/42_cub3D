/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/20 15:24:25 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Every function used for the mini map:
 *	
 *	void	initialize_line(t_game *game, t_line *line);
 *	void	draw_line_minimap(t_game *game);
 *	void	draw_player_square(t_game *game,
 *				t_mini_map *mini_map, unsigned int color);
 *	void	draw_a_block(t_game *game,
 *				t_mini_map *mini_map, unsigned int color);
 *	void	draw_minimap(t_game *game);
 */

/*
 * Initialisation of the line struct used by Brensenham algorithm
 */
void	initialize_line(t_game *game, t_line *line)
{
	line->x_start = game->mini_map.player_x;
	line->y_start = game->mini_map.player_y;
	line->x_end = game->mini_map.wall_x;
	line->y_end = game->mini_map.wall_y;
	line->delta_x = abs(line->x_end - line->x_start);
	line->delta_y = abs(line->y_end - line->y_start);
	if (line->x_start < line->x_end)
		line->sign_x = 1;
	else
		line->sign_x = -1;
	if (line->y_start < line->y_end)
		line->sign_y = 1;
	else
		line->sign_y = -1;
	line->error = line->delta_x - line->delta_y;
	line->error_tmp = 0;
}

/*
 * Brensenham algorithm to draw a line between tow points' coordinates
 */
void	draw_line_minimap(t_game *game)
{
	t_line	line;

	initialize_line(game, &line);
	while (1)
	{
		my_mlx_pixel_put(&game->mini_map.img,
			line.x_start, line.y_start, YELLOW);
		if (line.x_start == line.x_end && line.y_start == line.y_end)
			break ;
		line.error_tmp = 2 * line.error;
		if (line.error_tmp > -line.delta_y)
		{
			line.error -= line.delta_y;
			line.x_start += line.sign_x;
		}
		if (line.error_tmp < line.delta_x)
		{
			line.error += line.delta_x;
			line.y_start += line.sign_y;
		}
	}
}

/*
 * Draw a small square at the player coordinates
 */
void	draw_player_square(t_game *game,
			t_mini_map *mini_map, unsigned int color)
{
	int		x;
	int		y;

	y = 0;
	mini_map->player_x = (int)((game->player.pos_x * game->mini_map.img.width)
			/ (TILE_SIZE * game->file.width));
	mini_map->player_y = (int)((game->player.pos_y * game->mini_map.img.height)
			/ (TILE_SIZE * game->file.height));
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			my_mlx_pixel_put(&game->mini_map.img, x + mini_map->player_x,
				y + mini_map->player_y, color);
			x++;
		}
		y++;
	}
}

/*
 * Draw a block with exact pixel coordinates (xs = x_start, xe = x_end)
 */
void	draw_a_block(t_game *game,
			t_mini_map *mini_map, unsigned int color)
{
	int	x;
	int	y;

	y = mini_map->y_start;
	while (y < mini_map->y_end)
	{
		x = mini_map->x_start;
		while (x < mini_map->x_end)
		{
			my_mlx_pixel_put(&game->mini_map.img, x, y, color);
			x++;
		}
		y++;
	}
}

/*
 * Function to draw a minimap
 */
void	draw_minimap(t_game *game)
{
	t_mini_map	*mini;
	size_t		x;
	size_t		y;

	mini = &game->mini_map;
	y = 0;
	while (y < game->file.height)
	{
		mini->y_start = (y * mini->img.height) / game->file.height;
		mini->y_end = ((y + 1) * mini->img.height) / game->file.height;
		x = 0;
		while (x < game->file.width)
		{
			mini->x_start = (x * mini->img.width) / game->file.width;
			mini->x_end = ((x + 1) * mini->img.width) / game->file.width;
			if (game->file.map[y][x] == '1')
				draw_a_block(game, mini, RED);
			else
				draw_a_block(game, mini, BLUE);
			x++;
		}
		y++;
	}
	draw_player_square(game, mini, GREEN);
}
