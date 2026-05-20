/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:47:04 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/20 16:21:22 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	get_map_dimensions(t_file *file)
{
	size_t	y;
	size_t	current_len;

	y = 0;
	file->width = 0;
	while (file->map[y])
	{
		current_len = 0;
		while (file->map[y][current_len] != '\0'
				&& file->map[y][current_len] != '\n')
			current_len++;
		if (current_len > file->width)
			file->width = current_len;
		y++;
	}
	file->height = y;
}

void	replace_spaces_with_walls(t_file *file)
{
	size_t	y;
	size_t	x;
	char	*new_line;

	y = 0;
	while (file->map[y])
	{
		new_line = malloc(sizeof(char) * (file->width + 1));
		if (!new_line)
			error_exit("Memory allocation failed for rectangular map");
		ft_memset(new_line, '1', file->width);
		new_line[file->width] = '\0';
		x = 0;
		while (file->map[y][x] != '\0' && file->map[y][x] != '\n')
		{
			if (file->map[y][x] != ' ')
				new_line[x] = file->map[y][x];
			x++;
		}
		free(file->map[y]);
		file->map[y++] = new_line;
	}
}

void	convert_file_to_tab(t_file *file)
{
	size_t	i;
	char	*end;

	i = 0;
	file->file_content = malloc(sizeof(char *) * (file->height + 1));
	if (!file->file_content)
		error_exit("Memory allocation failed for file content");
	while (i < file->height)
	{
		file->file_content[i] = get_next_line(file->fd);
		i++;
	}
	end = get_next_line(file->fd);
	if (end)
		free(end);
	close(file->fd);
	file->file_content[i] = NULL;
}

void	init_file(t_file *file, char *filename)
{
	file->filename = filename;
	file->height = 0;
	file->width = 0;
	file->no = 0;
	file->so = 0;
	file->ea = 0;
	file->we = 0;
	file->f = 0;
	file->c = 0;
	file->fd = 0;
	file->player_count = 0;
}

size_t	check_file(t_file *file, t_textures *textures, int argc, char *filename)
{
	if (argc != 2)
		error_exit("Invalid number of arguments. Usage: ./cub3D <map.cub>");
	check_file_extension(filename);
	init_file(file, filename);
	check_file_existence(file);
	get_file_height(file);
	convert_file_to_tab(file);
	init_textures(textures);
	check_file_content(file->game, file, textures);
	return (0);
}
