/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:32:22 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/12 11:39:12 by nofelten         ###   ########.fr       */
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
void	check_file_existence(t_map *map)
{

	map->fd = open(map->filename, O_RDONLY);
	if (map->fd == -1)
		error_exit("file not found!");
}

// recuper la hauteur du fichier.
void	get_map_height(t_map *map)
{
	int	fd;
	char	*line;
	
	fd = open(map->filename, O_RDONLY);
	if (fd < 0)
		error_exit("Open");
	line = get_next_line(fd);
	while (line)
	{
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	convert_file_to_tab(t_map *map)
{
	size_t	i;

	i = 0;
	map->file_content = malloc(sizeof(char *) * (map->height + 1));
	if (!map->file_content)
		error_exit("Malloc");
	while (i < map->height)
	{
		map->file_content[i] = get_next_line(map->fd);
		i++;
	}
	map->file_content[i] = NULL; 
}

void	convert_map_to_tab(t_map *map, size_t height)
{
	size_t	i;

	i = 0;
	map->map = malloc(sizeof(char *) * (map->height - height) + 1);
	if (!map->map)
		error_exit("Malloc");
	while (height < map->height)
	{
		map->map[i] = map->file_content[height];
		height++;
		i++;
	}
	map->map[height] = NULL;
}

void	check_map_content(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->height)
	{
		i = skip_empty_line(map, i);
		if (!element_find(map))
			break ;
		check_element(map, i);
		i++;
	}
	i = skip_empty_line(map, i);
	convert_map_to_tab(map, i);
	i = 0;
	while (i < 14)
	{
		printf("%s", map->map[i]);
		i++;
	}

	//copie de la fin du ficher map donc normalement il ne reste que la map et je parse le tableau map pour check tout les element de la map.
}

void	check_element(t_map *map, size_t i)
{
	size_t	j;

	j = skip_space(map->file_content[i]);
	if (!ft_strncmp(&map->file_content[i][j], "NO ", 3) && map->north == 0)
		map->north = 1;
	else if (!ft_strncmp(&map->file_content[i][j], "SO ", 3) && map->south == 0)
		map->south = 1;
	else if (!ft_strncmp(&map->file_content[i][j], "WE ", 3) && map->west == 0)
		map->west = 1;
	else if (!ft_strncmp(&map->file_content[i][j], "EA ", 3) && map->east == 0)
		map->east = 1;
	else if (!ft_strncmp(&map->file_content[i][j], "F ", 2) && map->floor == 0)
		map->floor = 1;
	else if (!ft_strncmp(&map->file_content[i][j], "C ", 2) && map->ceiling == 0)
		map->ceiling = 1;
	else
		error_exit("Map file content is incorrect.");
	printf("%ld %ld %ld %ld %ld %ld\n", map->north, map->south, map->west, map->east, map->floor, map->ceiling);
}

int	element_find(t_map *map)
{
	if (map->north == 1)
	{
		if (map->south == 1)
		{
			if (map->east == 1)
			{
				if (map->west == 1)
				{
					if (map->floor == 1)
					{
						if (map->ceiling == 1)
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

size_t	skip_empty_line(t_map *map, size_t i)
{
	size_t	j;

	while (map->file_content[i])
	{
		j = 0;
		while (map->file_content[i][j])
		{
			if (!ft_isspace(map->file_content[i][j]))
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

void	init_map(t_map *map, char *filename)
{
	map->filename = filename;
	map->height = 0;
	map->width = 0;
	map->north = 0;
	map->south = 0;
	map->east = 0;
	map->west = 0;
	map->floor = 0;
	map->ceiling = 0;
	map->fd = 0;
}

int	check_map(int argc, char *filename)
{
	t_map	map;

	if (argc != 2)
		error_exit("Invalid arguments");
	check_file_extension(filename);
	init_map(&map, filename);
	check_file_existence(&map);
	get_map_height(&map);
	convert_file_to_tab(&map);
	check_map_content(&map);
	return (0);
}
