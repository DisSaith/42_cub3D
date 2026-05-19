/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:59:18 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/18 15:01:45 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t	check_rgb_range(int r, int g, int b)
{
	if ((r < 0 || r > 250)
		|| (g < 0 || g > 250)
		|| (b < 0 || b > 250))
		return (1);
	return (0);
}

void	fill_rgb(t_textures *textures, char *str, char *id)
{
	size_t	start;
	int		r;
	int		g;
	int		b;

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
		return (error_exit("Map file content is incorrect."), 0);
}
