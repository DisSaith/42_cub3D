/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:32:22 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/12 16:46:43 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// verifie l'exention du fichier.
void	check_file_extension(char *filename)
{
	size_t	len;

	if (!filename || !filename[0])
		error_exit("Invalid map file name");
	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
	{
		error_exit("Invalid map file extension");
	}
}
// verifie l'existence du fichier.
void	check_file_existence(t_file *file)
{
	file->fd = open(file->filename, O_RDONLY);
	if (file->fd == -1)
		error_exit("file not found!");
}

// recuper la hauteur du fichier.
void	get_file_height(t_file *file)
{
	int	fd;
	char	*line;
	
	fd = open(file->filename, O_RDONLY);
	if (fd < 0)
		error_exit("Open");
	line = get_next_line(fd);
	while (line)
	{
		file->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	convert_file_to_tab(t_file *file)
{
	size_t	i;

	i = 0;
	file->file_content = malloc(sizeof(char *) * (file->height + 1));
	if (!file->file_content)
		error_exit("Malloc");
	while (i < file->height)
	{
		file->file_content[i] = get_next_line(file->fd);
		i++;
	}
	file->file_content[i] = NULL; 
}

void	convert_map_to_tab(t_file *file, size_t height)
{
	size_t	i;

	i = 0;
	file->map = malloc(sizeof(char *) * (file->height - height) + 1);
	if (!file->map)
		error_exit("Malloc");
	while (height < file->height)
	{
		file->map[i] = file->file_content[height];
		height++;
		i++;
	}
	file->map[height] = NULL;
}

void	check_map_content(t_file *file)
{
	size_t	i;

	i = 0;
	while (i < file->height)
	{
		i = skip_empty_line(file, i);
		if (!element_find(file))
			break ;
		check_element(file, i);
		i++;
	}
	i = skip_empty_line(file, i);
	convert_map_to_tab(file, i);
	i = 0;
	while (i < 14)
	{
		printf("%s", file->map[i]);
		i++;
	}

//copie de la fin du ficher map donc normalement il ne reste que la map et je parse le tableau map pour check tout les element de la map.
}

void	check_element(t_file *file, size_t i)
{
	size_t	j;

	j = skip_space(file->file_content[i]);
	if (!ft_strncmp(&file->file_content[i][j], "NO ", 3) && file->north == 0)
		file->north = 1;
	else if (!ft_strncmp(&file->file_content[i][j], "SO ", 3) && file->south == 0)
		file->south = 1;
	else if (!ft_strncmp(&file->file_content[i][j], "WE ", 3) && file->west == 0)
		file->west = 1;
	else if (!ft_strncmp(&file->file_content[i][j], "EA ", 3) && file->east == 0)
		file->east = 1;
	else if (!ft_strncmp(&file->file_content[i][j], "F ", 2) && file->floor == 0)
		file->floor = 1;
	else if (!ft_strncmp(&file->file_content[i][j], "C ", 2) && file->ceiling == 0)
		file->ceiling = 1;
	else
		error_exit("Map file content is incorrect.");
	printf("%ld %ld %ld %ld %ld %ld\n", file->north, file->south, file->west, file->east, file->floor, file->ceiling);
}

int	element_find(t_file *file)
{
	if (file->north == 1)
	{
		if (file->south == 1)
		{
			if (file->east == 1)
			{
				if (file->west == 1)
				{
					if (file->floor == 1)
					{
						if (file->ceiling == 1)
							return (0);
						else
							return (1);
					}
					return (1);
				}
				return (1);
			}
			return (1);
		}
		return (1);
	}
	return (1);
}

size_t	skip_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	return (i);
}

size_t	skip_empty_line(t_file *file, size_t i)
{
	size_t	j;

	while (file->file_content[i])
	{
		j = 0;
		while (file->file_content[i][j])
		{
			if (!ft_isspace(file->file_content[i][j]))
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

void	init_file(t_file *file, char *filename)
{
	file->filename = filename;
	file->height = 0;
	file->width = 0;
	file->north = 0;
	file->south = 0;
	file->east = 0;
	file->west = 0;
	file->floor = 0;
	file->ceiling = 0;
	file->fd = 0;
}

int	check_map(int argc, char *filename)
{
	t_file	map;

	if (argc != 2)
		error_exit("Invalid arguments");
	check_file_extension(filename);
	init_file(&map, filename);
	check_file_existence(&map);
	get_file_height(&map);
	convert_file_to_tab(&map);
	check_map_content(&map);
	return (0);
}
