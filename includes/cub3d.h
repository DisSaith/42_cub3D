/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:59:22 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/21 13:51:08 by nofelten         ###   ########.fr       */
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
# define SHIFT_R_KEY 65505

# define TILE_SIZE 64

# define WIDTH_WINDOW 1280
# define HEIGHT_WINDOW 720

# define GREEN 0x0000FF00
# define RED 0x00FF0000
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
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

typedef struct s_column
{
	t_img	*texture;
	double	wall_x;
	double	step;
	double	tex_pos;
	int		tex_x;
	int		tex_y;
}			t_column;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plan_x;
	double	plan_y;
	int		mouse_x;
	int		mouse_y;
	char	cardinal_point;
	bool	w_press;
	bool	s_press;
	bool	d_press;
	bool	a_press;
	bool	right_press;
	bool	left_press;
	bool	shift_r_press;
}			t_player;

typedef struct s_textures
{
	t_img			north;
	t_img			south;
	t_img			west;
	t_img			east;
	char			*path_no;
	char			*path_so;
	char			*path_ea;
	char			*path_we;
	unsigned int	ceiling;
	unsigned int	floor;
}					t_textures;

typedef struct s_game	t_game;

typedef struct s_file
{
	char		*filename;
	char		**file_content;
	char		**map;
	size_t		height;
	size_t		width;
	size_t		no;
	size_t		so;
	size_t		ea;
	size_t		we;
	size_t		f;
	size_t		c;
	size_t		player_count;
	int			fd;
	t_game		*game;
}			t_file;

typedef struct s_line
{
	int		x_start;
	int		x_end;
	int		y_start;
	int		y_end;
	int		delta_x;
	int		delta_y;
	int		sign_x;
	int		sign_y;
	int		error;
	int		error_tmp;
}				t_line;

typedef struct s_mini_map
{
	t_img	img;
	double	wall_x_g;
	double	wall_y_g;
	int		wall_x;
	int		wall_y;
	int		x_start;
	int		x_end;
	int		y_start;
	int		y_end;
	int		player_x;
	int		player_y;
}			t_mini_map;

typedef struct s_game
{
	t_img		buffer;
	t_textures	textures;
	t_player	player;
	t_file		file;
	t_mini_map	mini_map;
	void		*mlx;
	void		*window;
}			t_game;

/**********main.c**********/
int				main(int argc, char **argv);

/**********PARSING***********/
//parsing.c
size_t			check_file(t_file *file, t_textures *texture,
					int argc, char *filename);
void			convert_file_to_tab(t_file *file);
void			init_file(t_file *file, char *filename);
void			replace_spaces_with_walls(t_file *file);
void			get_map_dimensions(t_file *file);
//file_parsing.c
size_t			check_element(t_file *file, t_textures *texture, size_t i);
void			get_file_height(t_file *file);
void			check_file_existence(t_file *file);
void			check_file_extension(char *filename);
void			check_file_content(t_game *game, t_file *file,
					t_textures *textures);
//map_parsing.c
char			get_map_char(t_file *file, int x, int y);
size_t			check_map_element(t_file *file, size_t x, size_t y);
void			check_map_content(t_game *game, t_file *file);
size_t			check_map_closed(t_file *file);
void			convert_map_to_tab(t_file *file, size_t height);
//textures_parsing.c
void			init_textures(t_textures *textures);
void			check_texture_file_existence(char *path);
void			check_texture_file_extension(char *filename);
void			fill_textures_filename(t_textures *textures,
					char *str, char *id);
//rgb_parsing.c
size_t			check_rgb_range(int *rgb);
size_t			check_rgb(t_file *file, t_textures *textures,
					size_t y, size_t x);
size_t			check_rgb_intruder(char *str, size_t *start);
void			fill_rgb(t_textures *textures, char *str, char *id);
//player_parsing.c
void			check_player_position(t_game *game, size_t x, size_t y);
void			init_player_vector(t_game *game, char direction);
//utils_parsing.c
size_t			skip_space(char *str);
size_t			back_space(char	*str);
size_t			is_floor_or_player(char c);
size_t			skip_empty_line(t_file *file, size_t i);
int				element_find(t_file *file, size_t n);

/**********UTILITIES***********/
//
//initialize_game.c
int				initialisation_game(t_game *game);
void			init_player(t_game *game);
//utils_cub3d.c
t_game			*get_game_ptr(t_game *ptr);
unsigned int	get_pixel_from_img(t_img *img, int x, int y);
unsigned int	create_trgb(int t, int r, int g, int b);
int				ft_atoi_cub3d(const char *str);
//key_manager.c
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
//move_player.c
int				check_collision(t_game *game, char direction,
					double dir_x, double dir_y);
void			rotate_fov(t_game *game, double rotation,
					double old_dir_x, double old_plan_x);
void			move_vertical(t_game *game, double speed);
void			move_horizontal(t_game *game, double speed);
void			move_player(t_game *game);
//free.c
int				close_game(t_game *game);
void			free_parsing_data(t_game *game);
void			free_mlx_data(t_game *game);
void			free_game_data(t_game *game);
//error.c
void			error_exit(char *error_message);

/**********RENDERING***********/
//
//load_textures.c
int				load_img(t_game *game, t_img *img, int width, int height);
int				load_textures(t_game *game);
int				load_xpm(t_game *game, t_img *img, char *path);
//rendering.c
void			my_mlx_pixel_put(t_img *img, int x, int y, unsigned int pixel);
void			draw_column(t_game *game, t_raycasting *ray,
					t_column *column, int x);
void			raycasting(t_game *game);
int				rendering(t_game *game);
//raycasting.c
void			initialize_ray1(t_game *game, t_raycasting *ray);
void			initialize_ray2(t_raycasting *ray);
void			perform_dda_algorithme(t_game *game, t_raycasting *ray);
void			initialize_column(t_game *game,
					t_raycasting *ray, t_column *column);
void			calculate_what_to_display(t_game *game, t_raycasting *ray,
					t_column *column);

/**********BONUS***********/
//
//raycasting_bonus.c
void			initialize_ray1(t_game *game, t_raycasting *ray);
void			initialize_ray2(t_raycasting *ray);
void			perform_dda_algorithme(t_game *game, t_raycasting *ray);
void			initialize_column(t_game *game,
					t_raycasting *ray, t_column *column);
void			calculate_what_to_display_b(t_game *game, t_raycasting *ray,
					t_column *column, t_mini_map *mini_map);
//minimap_bonus.c
void			initialize_line(t_game *game, t_line *line);
void			draw_line_minimap(t_game *game);
void			draw_player_square(t_game *game,
					t_mini_map *mini_map, unsigned int color);
void			draw_a_block(t_game *game,
					t_mini_map *mini_map, unsigned int color);
void			draw_minimap(t_game *game);
//rendering_bonus.c
void			my_mlx_pixel_put(t_img *img, int x, int y, unsigned int pixel);
void			draw_column(t_game *game, t_raycasting *ray,
					t_column *column, int x);
void			raycasting_b(t_game *game);
int				rendering_b(t_game *game);
//initialize_game_bonus.c
int				initialisation_game_b(t_game *game);
void			init_player_b(t_game *game);
//free_bonus.c
int				close_game_b(t_game *game);
void			free_mlx_data_b(t_game *game);
void			free_game_data_b(t_game *game);
void			error_exit_b(char *error_message);
//key_manager_bonus.c
int				key_press_b(int keycode, t_game *game);
int				key_release_b(int keycode, t_game *game);
//move_player_bonus.c
void			rotate_left_b(t_game *game, double rotation,
					double old_dir_x, double old_plan_x);
void			rotate_right_b(t_game *game, double rotation,
					double old_dir_x, double old_plan_x);
void			rotate_fov_b(t_game *game, double rotation,
					double old_dir_x, double old_plan_x);
void			move_player_b(t_game *game);

#endif
