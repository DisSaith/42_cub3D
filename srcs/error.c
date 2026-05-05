/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nofelten <nofelten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 12:13:11 by nofelten          #+#    #+#             */
/*   Updated: 2026/05/05 15:48:00 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_exit(char *error_message)
{
	size_t	n;

	n = ft_strlen(error_message);
	write(2, "Error\n", 7);
	write(2, error_message, n);
	write(2, "\n", 1);
	exit(1);
}
