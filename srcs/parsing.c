/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:32:22 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/18 17:10:07 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_file_extension(char *filename)
{
	size_t	len;

	if (!filename || !filename[0])
		error_exit("Invalid file name");
	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		error_exit("Invalid file extension");
}

void	check_texture_file_extension(char *filename)
{
	size_t	len;

	if (!filename || !filename[0])
		error_exit("Invalid texture file name");
	len = back_space(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".xpm", 4) != 0)
		error_exit("Invalid texture file extention");
}

void	check_file_existence(t_file *file)
{
	file->fd = open(file->filename, O_RDONLY);
	if (file->fd == -1)
	{
		close(file->fd);
		error_exit("File not found!");
	}
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
		error_exit("Malloc");
	ft_strncpy(filename, &path[x], len);
	filename[len] = '\0';
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		error_exit("Texture file not found!");
	}
	close(fd);
	free(filename);
}

void	get_file_height(t_file *file)
{
	int		fd;
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
	char	*end;

	i = 0;
	file->file_content = malloc(sizeof(char *) * (file->height + 1));
	if (!file->file_content)
		error_exit("Malloc");
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

void	convert_map_to_tab(t_file *file, size_t height)
{
	size_t	i;

	i = 0;
	file->map = malloc(sizeof(char *) * (file->height - height + 1));
	if (!file->map)
		error_exit("Malloc");
	while (height < file->height)
	{
		file->map[i] = file->file_content[height];
		height++;
		i++;
	}
	file->map[i] = NULL;
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
		error_exit("Malloc");
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

size_t	check_rgb_range(int r, int g, int b)
{
	if ((r < 0 || r > 250)
			|| (g < 0 || g > 250)
			|| (b < 0 || b > 250))
		return (1);
	return (0);
}

unsigned int	fill_rgb(t_textures *textures, char *str, char *id)
{
	size_t	start;
	int	r;
	int	g;
	int	b;

	start = 0;
	while (!ft_isdigit(str[start]))
		start++;
	r = ft_atoi(&str[start]);
	while (str[start] != ',')
		start++;
	start++;
	g = ft_atoi(&str[start]);
	while (str[start] != ',')
		start++;
	start++;
	b = ft_atoi(&str[start]);
	if (check_rgb_range(r, g, b))
		error_exit("Wrong rgb range");
	if (ft_strncmp(id, "F", 2) == 0)
		textures->floor = create_trgb(0, r, g, b);
	else
		textures->ceiling = create_trgb(0, r, g, b);
	return (0);
}

int	is_floor_or_player(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

char	get_map_char(t_file *file, int x, int y)
{
	int	line_len;
	int map_height;

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

int	check_map_closed(t_file *file)
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
				if (get_map_char(file, x, y - 1) == ' ' ||
					get_map_char(file, x, y + 1) == ' ' ||
					get_map_char(file, x - 1, y) == ' ' ||
					get_map_char(file, x + 1, y) == ' ')
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

void	check_map_content(t_file *file)
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
				error_exit("fichier map pas bon!");
			else if (file->map[y][x] == 'N' || file->map[y][x] == 'S' 
					|| file->map[y][x] == 'W' || file->map[y][x] == 'E')
				file->player_count++;
			x++;
		}
		y++;
	}
	if (file->player_count != 1)
		error_exit("Erreur : il doit y avoir exactement 1 joueur (N, S, W, E)");
}

void	check_file_content(t_file *file, t_textures *textures)
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
	check_map_content(file);
	if (!check_map_closed(file))
		error_exit("La map n'est pas fermee par des murs !");
}

size_t	check_rgb(t_file *file, t_textures *textures, size_t y, size_t x)
{
	if (!ft_strncmp(&file->file_content[y][x], "F ", 2) && file->F == 0)
	{
		fill_rgb(textures, file->file_content[y], "F");
		return (file->F = 1, 0);
	}
	else if (!ft_strncmp(&file->file_content[y][x], "C ", 2) && file->C == 0)
	{
		fill_rgb(textures, file->file_content[y], "C");
		return (file->C = 1, 0);
	}
	else
		return (error_exit("Map file content is incorrect."), 0);
}

size_t	check_element(t_file *file, t_textures *textures, size_t y)
{
	size_t	x;

	x = skip_space(file->file_content[y]);
	if (!ft_strncmp(&file->file_content[y][x], "NO ", 3) && file->NO == 0)
	{
		fill_textures_filename(textures, file->file_content[y], "NO");
		return (file->NO = 1, 1);
	}
	else if (!ft_strncmp(&file->file_content[y][x], "SO ", 3) && file->SO == 0)
	{
		fill_textures_filename(textures, file->file_content[y], "SO");
		return (file->SO = 1, 1);
	}
	else if (!ft_strncmp(&file->file_content[y][x], "WE ", 3) && file->WE == 0)
	{
		fill_textures_filename(textures, file->file_content[y], "WE");
		return (file->WE = 1, 1);
	}
	else if (!ft_strncmp(&file->file_content[y][x], "EA ", 3) && file->EA == 0)
	{
		fill_textures_filename(textures, file->file_content[y], "EA");
		return (file->EA = 1, 1);
	}
	else if (check_rgb(file, textures, y, x))
		return (0);
	return (0);
}

int	element_find(t_file *file, size_t n)
{
	if (n == 0)
	{
		if (file->NO == 1
			&& file->SO == 1
			&& file->EA == 1
			&& file->WE == 1
			&& file->F == 1
			&& file->C == 1)
			return (1);
	}
	if (n == 1)
	{
		if (file->NO == 2
			|| file->SO == 2
			|| file->EA == 2
			|| file->WE == 2)
			return (1);
	}
	return (0);
}

size_t	skip_space(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

size_t	back_space(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (ft_isspace(str[len - 1]))
		len--;
	return (len);
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
	file->NO = 0;
	file->SO = 0;
	file->EA = 0;
	file->WE = 0;
	file->F = 0;
	file->C = 0;
	file->fd = 0;
	file->player_count = 0;
}

void	init_textures(t_textures *textures)
{
	textures->path_no = NULL;
	textures->path_so = NULL;
	textures->path_ea = NULL;
	textures->path_we = NULL;
}

int	check_file(t_file *file, t_textures *textures, int argc, char *filename)
{
	if (argc != 2)
		error_exit("Invalid arguments");
	check_file_extension(filename);
	init_file(file, filename);
	check_file_existence(file);
	get_file_height(file);
	convert_file_to_tab(file);
	init_textures(textures);
	check_file_content(file, textures);
	return (0);
}
