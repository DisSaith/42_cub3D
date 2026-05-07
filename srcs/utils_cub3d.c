/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/07 12:08:11 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *Store and return the pointer of the main structure game with all data
 */
t_game	*get_game_ptr(t_game *ptr)
{
	static t_game	*game;

	if (ptr)
		game = ptr;
	return (game);
}
