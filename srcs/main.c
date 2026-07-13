/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:43:46 by mcastrat          #+#    #+#             */
/*   Updated: 2025/08/27 14:53:59 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static	int	init(t_game *game)
{
	game->moves = 0;
	game->game_over = 0;
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, game->map->width * TILE_SIZE,
			game->map->height * TILE_SIZE, "so_long..");
	if (!game->win)
		return (0);
	if (!load_textures(game))
		return (0);
	render_game(game);
	return (1);
}

static	int	valid_and_load_map(char *filename, t_map *map, t_game *game)
{
	game->map = map;
	if (!check_ext(filename))
		return (0);
	if (!load_map_data(filename, map))
		return (0);
	if (!check_rectangular(map) || !check_walls(map)
		|| !check_elements(map) || !check_path(map))
		return (error_map(map, "Error = Invalid map"), 0);
	return (1);
}

int	main(int ac, char **av)
{
	t_map	map;
	t_game	game;

	if (ac != 2)
		return (error_map(NULL, "Error = Usage: ./so_long map.ber"), 1);
	if (!valid_and_load_map(av[1], &map, &game))
		return (1);
	if (!init(&game))
		return (error_map(&map, "Error = Failed to initialize game"), 1);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	return (0);
}
