/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_wall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 15:48:04 by mcastrat          #+#    #+#             */
/*   Updated: 2025/08/29 00:04:14 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	check_walls(t_map *map)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < map->width)
	{
		if (map->grid[0][i] != '1' || map->grid[map->height - 1][i] != '1')
			return (error_map(map, "Error = NEED walls"), 0);
		i++;
	}
	i = -1;
	while (++i < map->height)
	{
		if (map->grid[i][0] != '1' || map->grid[i][map->width - 1] != '1')
			return (error_map(map, "Error = NEED walls"), 0);
		j = -1;
		while (++j < map->width)
		{
			c = map->grid[i][j];
			if (c != '1' && c != '0' && c != 'C' && c != 'E' && c != 'P')
				return (error_map(map, "Error = Invalid Char on the map"), 0);
		}
	}
	return (1);
}

static void	set_player_position(t_map *map, int j, int i)
{
	map->player_x = j;
	map->player_y = i;
}

static void	set_exit_position(t_map *map, int j, int i)
{
	map->exit_x = j;
	map->exit_y = i;
}

static int	scan_elements(t_map *map, int *player, int *exit)
{
	int	i;
	int	j;

	i = 0;
	*player = 0;
	*exit = 0;
	map->collectibles = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'P' && ++(*player))
				set_player_position(map, j, i);
			else if (map->grid[i][j] == 'E' && ++(*exit))
				set_exit_position(map, j, i);
			else if (map->grid[i][j] == 'C')
				map->collectibles++;
			else if (map->grid[i][j] != '1' && map->grid[i][j] != '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_elements(t_map *map)
{
	int	player;
	int	exit;

	if (!scan_elements(map, &player, &exit))
		return (0);
	return (player == 1 && exit == 1 && map->collectibles > 0);
}
