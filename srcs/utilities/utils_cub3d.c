/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cub3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:57:47 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/20 12:34:29 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

/*
 *Calculate the position of a specific pixel from an xpm img and return it
 */
unsigned int	get_pixel_from_img(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bits_per_pixels / 8));
	return (*(unsigned int *)pixel);
}

/*
 * Create and return an color trgb in unsigned int
 */
unsigned int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*
 * Modified atoi for cub3d
 */
int	ft_atoi_cub3d(const char *str)
{
	int	atoi;
	int	sign;
	int	i;

	sign = 1;
	atoi = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		atoi *= 10;
		atoi += str[i] - 48;
		i++;
	}
	return (atoi * sign);
}
