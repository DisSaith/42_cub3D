/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:54:28 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/20 16:26:33 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_textures(t_textures *textures)
{
	textures->path_no = NULL;
	textures->path_so = NULL;
	textures->path_ea = NULL;
	textures->path_we = NULL;
}

void	check_texture_file_extension(char *filename)
{
	size_t	len;

	if (!filename || !filename[0])
		error_exit("Invalid texture file name");
	len = back_space(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".xpm", 4) != 0)
		error_exit("Invalid texture file extension (must be .xpm)");
}

void	check_texture_file_existence(char *path)
{
	int		fd;
	int		x;
	int		len;
	char	*filename;

	x = 0;
	while (!(path[x] == '.'))
		x++;
	len = back_space(&path[x]);
	filename = malloc(sizeof(char) * (len + 1));
	if (!filename)
		error_exit("Memory allocation failed for texture path");
	ft_strncpy(filename, &path[x], len);
	filename[len] = '\0';
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(filename);
		error_exit("Texture file could not be opened or found");
	}
	close(fd);
	free(filename);
}

void	fill_textures_filename(t_textures *textures, char *str, char *id)
{
	size_t	start;
	size_t	end;
	char	*filename;

	start = 0;
	while (str[start] != '.')
		start++;
	end = back_space(str);
	filename = malloc(sizeof(char) * (end - start + 1));
	if (!filename)
		error_exit("Memory allocation failed for texture path");
	ft_strncpy(filename, &str[start], (end - start));
	filename[end - start] = '\0';
	if (ft_strncmp(id, "NO", 3) == 0)
		textures->path_no = filename;
	else if (ft_strncmp(id, "SO", 3) == 0)
		textures->path_so = filename;
	else if (ft_strncmp(id, "WE", 3) == 0)
		textures->path_we = filename;
	else if (ft_strncmp(id, "EA", 3) == 0)
		textures->path_ea = filename;
}
