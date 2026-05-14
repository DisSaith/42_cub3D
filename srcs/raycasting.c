/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 13:15:34 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/14 12:10:19 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 *	[FILE DESCRIPTION]
 * Function needed for raycasting :
 *
 *  void	initialize_ray1(t_game *game, t_raycasting *ray);
 *  void	initialize_ray2(t_game *game, t_raycasting *ray);
 *  void	perform_dda_algorithme(t_game *game, t_raycasting *ray);
 *  void	calculate_what_to_display(t_game *game, t_raycasting *ray);
 *  void	raycasting(t_game *game);
 */

/*
 * Initialize most of all variables of the raycasting struct :
 * Hit is set to 0 and will become 1 when the ray will hit a wall
 * Pos_x/_y are the current player position
 * Map_x/_y are the current ray position
 * Camera_x is the position on the plan (screen) to calculate the raydir
 * Raydir_x/_y are the ray direction in x and y
 * Deltaside_x/_y are length of ray from one x or y_side to next x or y_side
 */
void	initialize_ray1(t_game *game, t_raycasting *ray)
{
	ray->hit = 0;
	ray->player_pos_x = game->player.pos_x / 64.0;
	ray->player_pos_y = game->player.pos_y / 64.0;
	ray->map_x = (int)ray->player_pos_x;
	ray->map_y = (int)ray->player_pos_y;
	ray->camera_x = (2 * ray->x / (double)WIDTH_WINDOW) - 1;
	ray->raydir_x = game->player.dir_x + (game->player.plan_x * ray->camera_x);
	ray->raydir_y = game->player.dir_y + (game->player.plan_y * ray->camera_x);
	if (ray->raydir_x == 0)
		ray->deltadist_x = INFINITY;
	else
		ray->deltadist_x = fabs(1.0 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->deltadist_y = INFINITY;
	else
		ray->deltadist_y = fabs(1.0 / ray->raydir_y);
}

/*
 * Initialize Sidedist and Step :
 * Step_x/_y are what direction to step in x or y direction (either -1 or 1)
 * Sidedist_x/_y are the first length from start position to next x or y_side
 */
void	initialize_ray2(t_game *game, t_raycasting *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (ray->player_pos_x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - ray->player_pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (ray->player_pos_y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - ray->player_pos_y) * ray->deltadist_y;
	}
}

/*
 * DDA Algorithme :
 * Jump to the next map square either in x or y direction each time of the loop.
 * Stop when we a wall is hit by the ray
 */
void	perform_dda_algorithme(t_game *game, t_raycasting *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map.map[ray->map_y][ray->map_x] > 0)
			ray->hit = 1;
	}
}

/*
 * Calculate distance between player and the wall before calculate
 * the height line to draw on screen. After that we calculate the highest
 * and lowest pixels to fill in the current column
 */
void	calculate_what_to_display(t_game *game, t_raycasting *ray)
{
	if (ray->side == 0)
		ray->walldist = ray->sidedist_x - ray->deltadist_x;
	else
		ray->walldist = ray->sidedist_y - ray->deltadist_y;
	ray->lineheight = (int)(HEIGHT_WINDOW / ray->walldist);
	ray->drawstart = -(ray->lineheight / 2) + (HEIGHT_WINDOW / 2);
	if (ray->drawstart < 0)
		ray->drawstart = 0;
	ray->drawend = (ray->lineheight / 2) + (HEIGHT_WINDOW / 2);
	if (ray->drawend >= HEIGHT_WINDOW)
		ray->drawend = HEIGHT_WINDOW - 1;
}

/*
 * Perform raycasting :
 * Cast a ray in each column of the FOV player and calculate the distance
 * between the player and walls to determine what to display in 3D
 */
void	raycasting(t_game *game)
{
	t_raycasting	ray;

	ray.x = 0;
	while (ray.x < WIDTH_WINDOW)
	{
		initialize_ray1(game, &ray);
		initialize_ray2(game, &ray);
		perform_dda_algorithme(game, &ray);
		calculate_what_to_display(game, &ray);
		draw_column(game, &ray, ray.x);
		ray.x++;
	}
}
