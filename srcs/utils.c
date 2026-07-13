/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:13:50 by mcastrat          #+#    #+#             */
/*   Updated: 2025/08/27 14:54:11 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	error_map(t_map *map, char *message)
{
	ft_printf("%s\n", message);
	if (map)
		free_map(map);
}

int	close_game(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

void	cleanup_game(t_game *game)
{
	destroy_textures(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(game->map);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i])
			free(map->grid[i]);
		i++;
	}
	if (map->grid)
		free(map->grid);
	map->grid = NULL;
}
