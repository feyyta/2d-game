/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feita <feita@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:07:58 by mcastrat          #+#    #+#             */
/*   Updated: 2025/08/27 14:52:23 by feita            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line.h"
# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TILE_SIZE 64
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define UP_KEY 65362
# define LEFT_KEY 65361
# define DOWN_KEY 65364
# define RIGHT_KEY 65363

typedef struct s_map
{
	char	**grid;
	int		width;
	int		cols;
	int		height;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		collectibles;
	int		collected;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	*map;
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectible;
	void	*exit;
	int		moves;
	int		game_over;
}			t_game;

typedef struct s_path_data
{
	char	**grid;
	int		width;
	int		height;
	int		*collectibles;
	int		*exit_found;
	int		total;
}			t_path_data;

int			check_ext(char *filename);
int			load_map_data(char *filename, t_map *map);
int			check_path(t_map *map);
void		free_map(t_map *map);
void		cleanup_game(t_game *game);
int			load_textures(t_game *game);
void		destroy_textures(t_game *game);
void		render_game(t_game *game);
void		error_map(t_map *map, char *message);
int			close_game(t_game *game);
int			key_press(int keycode, t_game *game);
void		print_move_count(t_game *game);
void		free_temp_grid(char **temp_grid, int height);
int			check_elements(t_map *map);
int			check_walls(t_map *map);
int			check_rectangular(t_map *map);
void		handle_exit(t_game *game, int x, int y);

#endif