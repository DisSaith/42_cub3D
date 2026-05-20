/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:38:26 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/20 16:28:05 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	convert_map_to_tab(t_file *file, size_t height)
{
	size_t	i;

	i = 0;
	file->map = malloc(sizeof(char *) * (file->height - height + 1));
	if (!file->map)
		error_exit("Memory allocation failed for map array");
	while (height < file->height)
	{
		file->map[i] = ft_strdup(file->file_content[height]);
		if (!file->map[i])
			error_exit("Memory allocation failed for map line duplication");
		height++;
		i++;
	}
	file->map[i] = NULL;
}

char	get_map_char(t_file *file, int x, int y)
{
	int	line_len;
	int	map_height;

	map_height = 0;
	while (file->map[map_height])
		map_height++;
	if (y < 0 || y >= map_height)
		return (' ');
	line_len = 0;
	while (file->map[y][line_len] != '\0' && file->map[y][line_len] != '\n')
		line_len++;
	if (x < 0 || x >= line_len)
		return (' ');
	return (file->map[y][x]);
}

size_t	check_map_element(t_file *file, size_t x, size_t y)
{
	if (file->map[y][x] == '1'
		|| file->map[y][x] == '0'
		|| file->map[y][x] == ' '
		|| file->map[y][x] == 'N'
		|| file->map[y][x] == 'S'
		|| file->map[y][x] == 'W'
		|| file->map[y][x] == 'E')
		return (1);
	return (0);
}

size_t	check_map_closed(t_file *file)
{
	int	y;
	int	x;

	y = 0;
	while (file->map[y])
	{
		x = 0;
		while (file->map[y][x] != '\0' && file->map[y][x] != '\n')
		{
			if (is_floor_or_player(file->map[y][x]))
			{
				if (get_map_char(file, x, y - 1) == ' '
					|| get_map_char(file, x, y + 1) == ' '
					|| get_map_char(file, x - 1, y) == ' '
					|| get_map_char(file, x + 1, y) == ' ')
				{
					return (0);
				}
			}
			x++;
		}
		y++;
	}
	return (1);
}

void	check_map_content(t_game *game, t_file *file)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (file->map[y])
	{
		x = 0;
		while (file->map[y][x] != '\n' && file->map[y][x] != '\0')
		{
			if (!check_map_element(file, x, y))
				error_exit("Invalid character found in the map");
			else if (file->map[y][x] == 'N' || file->map[y][x] == 'S'
					|| file->map[y][x] == 'W' || file->map[y][x] == 'E')
			{
				file->player_count++;
				check_player_position(game, x, y);
				file->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	if (file->player_count != 1)
		error_exit("Map must contain exactly one player starting position");
}
