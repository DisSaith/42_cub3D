/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acohaut <acohaut@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 16:59:22 by acohaut           #+#    #+#             */
/*   Updated: 2026/05/04 18:08:52 by acohaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include <fcntl.h>

# define W_KEY 119
# define S_KEY 115
# define D_KEY 100
# define A_KEY 97
# define ESC_KEY 65307

typedef struct s_game
{
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
int		handle_key(int keycode, void *mlx);

/**********test_mlx.c**********/
int		draw_a_line(t_game *game, int x, int y);

#endif
