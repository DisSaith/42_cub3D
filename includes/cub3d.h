/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:59:22 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/14 16:56:11 by nofelten         ###   ########.fr       */
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
# include <stdbool.h>

# define W_KEY 119
# define S_KEY 115
# define D_KEY 100
# define A_KEY 97
# define ESC_KEY 65307
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

# define TILE_SIZE 64

# define WIDTH_WINDOW 640
# define HEIGHT_WINDOW 640

# define PI 3.14159265359

# define GREEN 0x0000FF00
# define RED 0x00FF0000
# define BLUE 0x000000FF
# define TRANSPARENT 0xFF000000

# define CEILING_COLOR  0x00383838
# define FLOOR_COLOR    0x00787060
# define WALL_NS_COLOR  0x00CCCCCC
# define WALL_EW_COLOR  0x00888888

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bits_per_pixels;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_raycasting
{
	double	player_pos_x;
	double	player_pos_y;
	double	raydir_x;
	double	raydir_y;
	double	camera_x;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	walldist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		x;
}			t_raycasting;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plan_x;
	double	plan_y;
	double	angle;
	bool	w_press;
	bool	s_press;
	bool	d_press;
	bool	a_press;
	bool	right_press;
	bool	left_press;
}			t_player;

typedef struct s_map
{
	int			**map;
	size_t		height;
	size_t		width;
	int			fd;
}			t_map;


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

typedef struct s_game
{
	t_img		buffer;
	t_img		wall;
	t_img		enemy;
	t_player	player;
	t_file		file;
	t_map		map;
	void		*mlx;
	void		*window;
	double		cur_time;
	double		old_time;
}			t_game;

/************error.c**************/
void			error_exit(char *error_message);

/**********main.c**********/
int				close_game(t_game *game);
int				initialize_map(t_game *game);
int				initialisation_game(t_game *game);
void			init_player(t_game *game);
int				main(int argc, char **argv);

/**********parsing.c***********/
void		check_file_extension(char *filename);
void		check_texture_file_extension(char *filename);
void		check_file_existence(t_file *file);
void    	convert_file_to_tab(t_file *file);
void    	get_map_height(t_file *file);
void    	check_map_content(t_file *file);
void    	init_file(t_file *file, char *filename);
void		check_map_element(t_file *file);
int     	check_file(t_file *file, int argc, char *filename);
int		element_find(t_file *file, size_t n);
size_t		skip_space(char *str);
size_t		back_space(char	*str);
size_t		skip_empty_line(t_file *file, size_t i);
size_t    	check_element(t_file *file,t_textures *texture, size_t i);

/**********utils_cub3d.c**********/
t_game			*get_game_ptr(t_game *ptr);

/**********key_manager.c**********/
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);

/**********move_player.c**********/
int				check_collision(t_game *game, char direction,
					double dir_x, double dir_y);
void			rotate_fov(t_game *game, double rotation,
					double old_dir_x, double old_plan_x);
void			move_vertical(t_game *game, double speed);
void			move_horizontal(t_game *game, double speed);
void			move_player(t_game *game);

/**********rendering.c**********/
unsigned int	get_pixel_from_img(t_img *img, int x, int y);
void			my_mlx_pixel_put(t_img *img, int x, int y, unsigned int pixel);
void			draw_sprite(t_game *game, t_img *sprite, int x, int y);
void			draw_column(t_game *game, t_raycasting *ray, int x);
int				rendering(t_game *game);

/**********load_textures.c**********/
int				load_buffer(t_game *game);
int				load_textures(t_game *game);
int				load_xpm(t_game *game, t_img *img, char *path);

/**********test_mlx.c**********/
void			draw_a_line(t_game *game, int x, int y);
void			draw_background(t_game *game, int color);
int				touch(t_game *game, double x, double y);
int				check_collision_2d(t_game *game, float speed);
void			move_player_2d(t_game *game);
int				rendering_2d(t_game *game);

/**********raycasting.c**********/
void			initialize_ray1(t_game *game, t_raycasting *ray);
void			initialize_ray2(t_game *game, t_raycasting *ray);
void			perform_dda_algorithme(t_game *game, t_raycasting *ray);
void			calculate_what_to_display(t_game *game, t_raycasting *ray);
void			raycasting(t_game *game);

#endif
