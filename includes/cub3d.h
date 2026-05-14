/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:59:22 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/12 13:15:25 by nofelten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

# define W_KEY 119
# define S_KEY 115
# define D_KEY 100
# define A_KEY 97
# define ESC_KEY 65307
# define LEFT_KEY 65361
# define RIGHT_KEY 65367

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
	double	x;
	double	y;
	char	direction;
	bool	w_press;
	bool	s_press;
	bool	d_press;
	bool	a_press;
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

typedef struct s_textures
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
}		t_textures;

typedef struct s_file
{
	char		*filename;
	char		**file_content;
	char		**map;
	size_t		height;
	size_t		width;
	size_t		NO;
	size_t		SO;
	size_t		EA;
	size_t		WE;
	size_t		F;
	size_t		C;
	int		fd;
}			t_file;

/************error.c**************/
void			error_exit(char *error_message);

/**********main.c**********/
int				close_game(t_game *game);
int				initialisation_game(t_game *game);
void			init_player(t_game *game);
int				main(int argc, char **argv);

/**********parsing.c***********/
void		check_file_extension(char *filename);
void		check_texture_file_extension(char *filename);
void		check_file_existence(t_file *file);
void    	convert_file_to_tab(t_file *file);
void    	get_map_height(t_file *file);
void    	check_map_content(t_file *file, t_textures *textures);
void    	init_file(t_file *file, char *filename);
int     	check_file(int argc, char *filename);
int		element_find(t_file *file);
size_t		skip_space(char *str);
size_t		back_space(char	*str);
size_t		skip_empty_line(t_file *file, size_t i);
size_t    	check_element(t_file *file,t_textures *texture, size_t i);

/**********utils_cub3d.c**********/
t_game			*get_game_ptr(t_game *ptr);

/**********key_manager.c**********/
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				check_collision(t_game *game, float speed);
void			move_player(t_game *game);

/**********rendering.c**********/
unsigned int	get_pixel_from_img(t_img *img, int x, int y);
void			my_mlx_pixel_put(t_img *img, int x, int y, unsigned int pixel);
void			draw_sprite(t_game *game, t_img *sprite, int x, int y);
int				rendering(t_game *game);

/**********load_textures.c**********/
int				load_buffer(t_game *game);
int				load_textures(t_game *game);
int				load_xpm(t_game *game, t_img *img, char *path);

/**********test_mlx.c**********/
void			draw_a_line(t_game *game, int x, int y);
void			draw_background(t_game *game, int color);

#endif
