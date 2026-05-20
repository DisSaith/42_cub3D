/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:31:34 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/20 16:01:06 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_file_extension(char *filename)
{
	size_t	len;

	if (!filename || !filename[0])
		error_exit("Invalid file name");
	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		error_exit("Invalid file extension");
}

void	check_file_existence(t_file *file)
{
	file->fd = open(file->filename, O_RDONLY);
	if (file->fd == -1)
	{
		error_exit("File not found!");
	}
}

void	get_file_height(t_file *file)
{
	int		fd;
	char	*line;

	fd = open(file->filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open the file");
	line = get_next_line(fd);
	while (line)
	{
		file->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	check_file_content(t_game *game, t_file *file, t_textures *textures)
{
	size_t	y;
	size_t	return_value;

	y = 0;
	return_value = 0;
	while (y < file->height)
	{
		y = skip_empty_line(file, y);
		if (element_find(file, 0))
			break ;
		return_value = check_element(file, textures, y);
		if (return_value == 1)
		{
			check_texture_file_extension(file->file_content[y]);
			check_texture_file_existence(file->file_content[y]);
		}
		y++;
	}
	y = skip_empty_line(file, y);
	convert_map_to_tab(file, y);
	get_map_dimensions(file);
	check_map_content(game, file);
	if (!check_map_closed(file))
		error_exit("Map is not properly enclosed by walls");
	replace_spaces_with_walls(file);
}

size_t	check_element(t_file *file, t_textures *textures, size_t y)
{
	size_t	x;

	x = skip_space(file->file_content[y]);
	if (!ft_strncmp(&file->file_content[y][x], "NO ", 3) && file->no == 0)
	{
		fill_textures_filename(textures, file->file_content[y], "NO");
		return (file->no = 1, 1);
	}
	else if (!ft_strncmp(&file->file_content[y][x], "SO ", 3) && file->so == 0)
	{
		fill_textures_filename(textures, file->file_content[y], "SO");
		return (file->so = 1, 1);
	}
	else if (!ft_strncmp(&file->file_content[y][x], "WE ", 3) && file->we == 0)
	{
		fill_textures_filename(textures, file->file_content[y], "WE");
		return (file->we = 1, 1);
	}
	else if (!ft_strncmp(&file->file_content[y][x], "EA ", 3) && file->ea == 0)
	{
		fill_textures_filename(textures, file->file_content[y], "EA");
		return (file->ea = 1, 1);
	}
	else
		return (check_rgb(file, textures, y, x), 0);
}
