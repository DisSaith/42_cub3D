/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 13:15:34 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/12 14:09:59 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Function needed for raycasting :
 * t
 */

int	raycasting(t_game *game)
{
	t_raycasting	ray;

	ray.x = 0;
	while (ray.x < WIDTH_WINDOW)
	{
		ray.hit = 0;
		ray.pos_x = game->player.pos_x / 64.0;
		ray.pos_y = game->player.pos_y / 64.0;
		//calculate ray position and direction
		ray.camera_x = 2 * ray.x / (double)WIDTH_WINDOW - 1;
		ray.raydir_x = game->player.dir_x + game->player.plan_x * ray.camera_x;
		ray.raydir_y = game->player.dir_y + game->player.plan_y * ray.camera_x;
		//which square of the map we are in
		ray.map_x = (int)ray.pos_x;
		ray.map_y = (int)ray.pos_y;
		//length of ray from one x or y-side to next x or y-side
		//security for division by zero :
		if (ray.raydir_y == 0) //if no vertical lines will be hit by the ray
			ray.deltadist_y = 1e30;
		else
			ray.deltadist_y = fabs(1 / ray.raydir_y);
		if (ray.raydir_x == 0)
			ray.deltadist_x = 1e30;
		else
			ray.deltadist_x = fabs(1 / ray.raydir_x);
		//calculte step and initial sidedist
		//step_x and step_y are what drection to step in x or y-direction (either -1 or +1)
		//sidedist_x and sidedist_y are length of ray from current position to next x or y-side
		if (ray.raydir_x < 0)
		{
			ray.step_x = -1;
			ray.sidedist_x = (ray.pos_x - ray.map_x) * ray.deltadist_x;
		}
		else
		{
			ray.step_x = 1;
			ray.sidedist_x = (ray.map_x + 1.0 - ray.pos_x) * ray.deltadist_x;
		}
		if (ray.raydir_y < 0)
		{
			ray.step_y = -1;
			ray.sidedist_y = (ray.pos_y - ray.map_y) * ray.deltadist_y;
		}
		else
		{
			ray.step_y = 1;
			ray.sidedist_y = (ray.map_y + 1.0 - ray.pos_y) * ray.deltadist_y;
		}
		//perform DDA algorithme
		while (ray.hit == 0)
		{
			//jump to the next map square, either in x or y-direction
			if (ray.sidedist_x < ray.sidedist_y)
			{
				ray.sidedist_x += ray.deltadist_x;
				ray.map_x += ray.step_x;
				ray.side = 0; //wall NS (face E or W)
			}
			else
			{
				ray.sidedist_y += ray.deltadist_y;
				ray.map_y += ray.step_y;
				ray.side = 1;//wall EW (face N or S)
			}
			//check if the ray has hit a wall
			if (game->map.map[ray.map_y][ray.map_x] > 0)
				ray.hit = 1;
		}
		//calculate de distance between the wall and the player position
		if (ray.side == 0)
			ray.walldist = (ray.sidedist_x - ray.deltadist_x);
		else
			ray.walldist = (ray.sidedist_y - ray.deltadist_y);
		//calculate height line to draw on screen
		ray.lineheight = (int)(HEIGHT_WINDOW / ray.walldist);
		//calculate lowest and highest pixel to fill in current stripe
		ray.drawstart = -ray.lineheight / 2 + HEIGHT_WINDOW / 2;
		if (ray.drawstart < 0)
			ray.drawstart = 0;
		ray.drawend = ray.lineheight / 2 + HEIGHT_WINDOW / 2;
		if (ray.drawend >= HEIGHT_WINDOW)
			ray.drawend = HEIGHT_WINDOW - 1;
		draw_column(game, &ray, ray.x);
		ray.x++;
	}
	return (1);
}
