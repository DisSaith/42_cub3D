/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:32:22 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/05 11:14:09 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_file_extension(char *file_name)
{
	char	*file_extension;
	size_t	i;
	size_t	j;

	if (!file_name || !file_name[0])
		return (1);
	i = ft_strlen(file_name + 1);
	j = 3;
	file_extension = malloc(sizeof(char *) * 5);
	file_extension[0] = '.';
	file_extension[1] = 'c';
	file_extension[2] = 'u';
	file_extension[3] = 'b';
	file_extension[4] = '\0';
	while (j > 0)
	{
		if (file_name[i] != file_extension[j])
			return (free(file_extension), 1);
		i--;
		j--;
	}
	free(file_extension);
	return (0);
}
