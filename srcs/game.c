/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:13:15 by mcastrat          #+#    #+#             */
/*   Updated: 2025/08/27 14:53:53 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	destroy_textures(t_game *game)
{
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->floor)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->collectible)
		mlx_destroy_image(game->mlx, game->collectible);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
}

int	load_textures(t_game *game)
{
	int	width;
	int	height;

	game->wall = mlx_xpm_file_to_image(game->mlx, "img/wall/wall.xpm", &width,
			&height);
	game->floor = mlx_xpm_file_to_image(game->mlx, "img/floor/wooden.xpm",
			&width, &height);
	game->player = mlx_xpm_file_to_image(game->mlx, "img/player/player.xpm",
			&width, &height);
	game->collectible = mlx_xpm_file_to_image(game->mlx,
			"img/collectible/collectible.xpm", &width, &height);
	game->exit = mlx_xpm_file_to_image(game->mlx, "img/exit/exit.xpm", &width,
			&height);
	if (!game->wall || !game->floor || !game->player || !game->collectible
		|| !game->exit)
		return (0);
	return (1);
}

static void	render_background(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			if (game->map->grid[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall, x, y);
			else
				mlx_put_image_to_window(game->mlx, game->win, game->floor, x,
					y);
			j++;
		}
		i++;
	}
}

static void	render_elements(t_game *game)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < game->map->height)
	{
		j = 0;
		while (j < game->map->width)
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			if (game->map->grid[i][j] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->player, x,
					y);
			else if (game->map->grid[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collectible,
					x, y);
			else if (game->map->grid[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit, x, y);
			j++;
		}
		i++;
	}
}

void	render_game(t_game *game)
{
	render_background(game);
	render_elements(game);
}
