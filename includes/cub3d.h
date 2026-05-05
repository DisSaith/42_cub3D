/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:59:22 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/05 16:09:07 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>

# define W_KEY 119
# define S_KEY 115
# define D_KEY 100
# define A_KEY 97
# define ESC_KEY 65307

# define TILE_SIZE 8

# define WIDTH_WINDOW 480
# define HEIGHT_WINDOW 480

# define GREEN 0x0000FF00
# define RED 0x00FF0000
# define BLUE 0x000000FF

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bits_per_pixels;
	int		line_len;
	int		endian;
}			t_img;

typedef struct s_game
{
	t_img	img;
	void	*mlx;
	void	*window;
	int		x_player;
	int		y_player;
}			t_game;

/**********main.c**********/
int	close_game(t_game *game);
int	initialisation_game(t_game *game);
int main(int argc, char **argv);

/**********utils_cub3d.c**********/
t_game	*get_game_ptr(t_game *ptr);
void	move_player(t_game *game, int dir_x, int dir_y);
int		handle_key(int keycode, void *s_game_ptr);

/**********test_mlx.c**********/
void	draw_a_line(t_game *game, int x, int y);
void	draw_background(t_game *game, int color);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int		load_buffer(t_game *game);
int		rendering(void);

#endif
