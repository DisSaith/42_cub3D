/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:32:22 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/07 10:59:04 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	check_file_existence(t_map *map, char *filename)
{

	map->fd = open(filename, O_RDONLY);
	if (map->fd == -1)
		error_exit("file not found!");
}

void	convert_file_to_tab(t_map *map, int fd)
{
	char	**file_content;
	size_t	i;

	i = 0;
	while (get_next_line(fd))
		map->height++;
	file_content = malloc(sizeof(char *) * map->height + 1);
	if (!file_content)
		error_exit("Malloc");
	while (i < map->height)
	{
		file_content[i] = get_next_line(fd);
		i++;
	}
	file_content[i] = NULL;
}

/*
void	check_map_content(char **map)
{

}
*/
void	init_map(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->fd = 0;
}

int	check_map(int argc, char *filename)
{
	t_map	map;

	if (argc != 2)
		error_exit("Invalid arguments");
	check_file_extension(filename);
	init_map(&map);
	check_file_existence(&map, filename);
	convert_file_to_tab(&map, map.fd);
	return (0);
}
