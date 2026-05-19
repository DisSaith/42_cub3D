/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:26:01 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/18 15:26:15 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

size_t	back_space(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	while (ft_isspace(str[len - 1]))
		len--;
	return (len);
}

size_t	skip_space(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (i);
}

size_t	is_floor_or_player(char c)
{
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	element_find(t_file *file, size_t n)
{
	if (n == 0)
	{
		if (file->no == 1
			&& file->so == 1
			&& file->ea == 1
			&& file->we == 1
			&& file->f == 1
			&& file->c == 1)
			return (1);
	}
	if (n == 1)
	{
		if (file->no == 2
			|| file->so == 2
			|| file->ea == 2
			|| file->we == 2)
			return (1);
	}
	return (0);
}
