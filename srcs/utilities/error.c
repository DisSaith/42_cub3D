/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:13:11 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/20 12:34:13 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
 * Free all data and display error message
 */
void	error_exit(char *error_message)
{
	size_t	n;

	free_game_data(get_game_ptr(NULL));
	n = ft_strlen(error_message);
	write(2, "Error\n", 7);
	write(2, error_message, n);
	write(2, "\n", 1);
	exit(1);
}
