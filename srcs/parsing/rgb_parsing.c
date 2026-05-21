/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:59:18 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/21 13:54:26 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t	check_rgb_range(int *rgb)
{
	if ((rgb[0] < 0 || rgb[0] > 255)
		|| (rgb[1] < 0 || rgb[1] > 255)
		|| (rgb[2] < 0 || rgb[2] > 255))
		return (0);
	return (1);
}

void	fill_rgb(t_textures *textures, char *str, char *id)
{
	size_t	start;
	int		rgb[3];

	start = (skip_space(str) + 1);
	start += (skip_space(&str[start]));
	if (str[start] != '-' && !ft_isdigit(str[start]))
		error_exit("Invalid character found in RGB format");
	rgb[0] = ft_atoi_cub3d(&str[start]);
	if ((!check_rgb_intruder(str, &start)))
		error_exit("RGB values must be strictly between 0 and 255");
	rgb[1] = ft_atoi_cub3d(&str[start]);
	if ((!check_rgb_intruder(str, &start)))
		error_exit("RGB values must be strictly between 0 and 255");
	rgb[2] = ft_atoi_cub3d(&str[start]);
	if (!check_rgb_range(rgb))
		error_exit("RGB values must be strictly between 0 and 255");
	while (ft_isdigit(str[start]))
		start++;
	if (!ft_isspace(str[start]))
		error_exit("Trailing garbage characters found after RGB values");
	if (ft_strncmp(id, "F", 2) == 0)
		textures->floor = create_trgb(0, rgb[0], rgb[1], rgb[2]);
	else
		textures->ceiling = create_trgb(0, rgb[0], rgb[1], rgb[2]);
}

size_t	check_rgb_intruder(char *str, size_t *start)
{
	while (ft_isdigit(str[(*start)]))
		(*start)++;
	if (str[(*start)] == ',')
	{
		(*start)++;
		return (1);
	}
	return (0);
}

size_t	check_rgb(t_file *file, t_textures *textures, size_t y, size_t x)
{
	if (!ft_strncmp(&file->file_content[y][x], "F ", 2) && file->f == 0)
	{
		fill_rgb(textures, file->file_content[y], "F");
		return (file->f = 1, 0);
	}
	else if (!ft_strncmp(&file->file_content[y][x], "C ", 2) && file->c == 0)
	{
		fill_rgb(textures, file->file_content[y], "C");
		return (file->c = 1, 0);
	}
	else
		return (error_exit("Unknown element identifier found in file"), 0);
}
