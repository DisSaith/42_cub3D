/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 17:32:22 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/05 15:45:21 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_file_extension(char *filename)
{
	char	*file_extension;
	size_t	i;
	size_t	j;

	if (!filename || !filename[0])
		error_exit("Invalid map file name");
	i = ft_strlen(filename + 1);
	j = 3;
	file_extension = malloc(sizeof(char *) * 5);
	file_extension[0] = '.';
	file_extension[1] = 'c';
	file_extension[2] = 'u';
	file_extension[3] = 'b';
	file_extension[4] = '\0';
	while (j > 0)
	{
		if (filename[i] != file_extension[j])
		{
			free(file_extension);
			error_exit("Invalid map file extension");
		}
		i--;
		j--;
	}
	free(file_extension);
}

void	check_file_existence(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_exit("file not found!");
}

/*
void	get_map_height()
{

}

void	get_map_width()
{

}

void	converte_map_to_tab(char *filename)
{
	
}

void	check_map_content(char **map)
{

}
*/
int	main(int argc, char **argv)
{
	(void)argc;
	check_file_extension(argv[1]);
	check_file_existence(argv[1]);
	return (0);
}
