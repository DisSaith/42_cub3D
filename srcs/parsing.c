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

int	checkFileExtension(char *fileName)
{
	char	*fileExtension;
	size_t	i;
	size_t	j;

	if (!fileName || !fileName[0])
		return (1);
	i = ft_strlen(fileName + 1);
	j = 3;
	fileExtension = malloc(sizeof(char *) * 5);
	fileExtension[0] = '.';
	fileExtension[1] = 'c';
	fileExtension[2] = 'u';
	fileExtension[3] = 'b';
	fileExtension[4] = '\0';
	while (j > 0)
	{
		if (fileName[i] != fileExtension[j])
			return (free(fileExtension), 1);
		i--;
		j--;
	}
	free(fileExtension);
	return (0);
}
