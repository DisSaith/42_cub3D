/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:47:04 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/19 14:58:30 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	init_file(t_file *file, char *filename)
{
	file->filename = filename;
	file->height = 0;
	file->width = 0;
	file->no = 0;
	file->so = 0;
	file->ea = 0;
	file->we = 0;
	file->f = 0;
	file->c = 0;
	file->fd = 0;
	file->player_count = 0;
}

size_t	check_file(t_file *file, t_textures *textures, int argc, char *filename)
{
	if (argc != 2)
		error_exit("Invalid arguments");
	check_file_extension(filename);
	init_file(file, filename);
	check_file_existence(file);
	get_file_height(file);
	convert_file_to_tab(file);
	init_textures(textures);
	check_file_content(file->game, file, textures);
	return (0);
}
