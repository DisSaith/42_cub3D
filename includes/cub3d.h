/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:59:22 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/06 15:45:02 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

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
# define TRANSPARENT 0xFF000000

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bits_per_pixels;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		x;
	int		y;
}			t_img;

typedef struct s_player
{
	int		x;
	int		y;
	char	direction;
}			t_player;

typedef struct s_game
{
	t_img		buffer;
	t_img		wall;
	t_img		enemy;
	t_player	player;
	void		*mlx;
	void		*window;
}			t_game;

/**********main.c**********/
int	close_game(t_game *game);
int	initialisation_game(t_game *game);
int main(int argc, char **argv);

/**********utils_cub3d.c**********/
t_game	*get_game_ptr(t_game *ptr);
void	move_player(t_game *game, int dir_x, int dir_y, char direction);
int		handle_key(int keycode, void *s_game_ptr);

/**********test_mlx.c**********/
unsigned int	get_pixel_from_img(t_img *img, int x, int y);
int				load_buffer(t_game *game);
int				load_textures(t_game *game);
int				load_xpm(t_game *game, t_img *img, char *path);
int				rendering(void);
void			draw_a_line(t_game *game, int x, int y);
void			draw_background(t_game *game, int color);
void			draw_sprite(t_game *game, t_img *sprite, int x, int y);
void			my_mlx_pixel_put(t_img *img, int x, int y, unsigned int pixel);

#endif
