/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:32:22 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/06 12:07:35 by nofelten         ###   ########.fr       */
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

/*
void	get_map_height()
{

}
*/
/*
void	get_map_width()
{

}
*/

void	convert_map_to_tab(int fd)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
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
	converte_map_to_tab(map.fd);
	return (0);
}
