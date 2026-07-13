/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_rect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 18:18:04 by mcastrat          #+#    #+#             */
/*   Updated: 2025/09/01 15:33:57 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	check_rectangular(t_map *map)
{
	int	i;
	int	expected_width;
	int	current_width;

	if (!map || !map->grid || map->height <= 0)
		return (0);
	if (!map->grid[0])
		return (0);
	expected_width = ft_strlen(map->grid[0]);
	if (expected_width <= 0)
		return (0);
	i = 0;
	while (i < map->height)
	{
		if (!map->grid[i])
			return (0);
		current_width = ft_strlen(map->grid[i]);
		if (current_width != expected_width)
			return (0);
		i++;
	}
	map->width = expected_width;
	return (1);
}

static int	path_check(t_path_data *data, int x, int y)
{
	if (x < 0 || x >= data->width || y < 0 || y >= data->height
		|| data->grid[y][x] == '1' || data->grid[y][x] == 'V')
		return (0);
	if (data->grid[y][x] == 'E' && *(data->collectibles) < data->total)
		return (0);
	if (data->grid[y][x] == 'C')
		(*(data->collectibles))++;
	if (data->grid[y][x] == 'E')
		*(data->exit_found) = 1;
	data->grid[y][x] = 'V';
	path_check(data, x + 1, y);
	path_check(data, x - 1, y);
	path_check(data, x, y + 1);
	path_check(data, x, y - 1);
	return (1);
}

static char	**create_temp_grid(t_map *map)
{
	char	**temp_grid;
	int		i;
	int		j;

	temp_grid = malloc(sizeof(char *) * map->height);
	if (!temp_grid)
		return (NULL);
	i = -1;
	while (++i < map->height)
	{
		temp_grid[i] = malloc(map->width + 1);
		if (!temp_grid[i])
			return (free_temp_grid(temp_grid, i + 1), NULL);
		j = -1;
		while (++j < map->width)
			temp_grid[i][j] = map->grid[i][j];
		temp_grid[i][j] = '\0';
	}
	return (temp_grid);
}

int	check_path(t_map *map)
{
	t_path_data	data;
	int			collectibles_found;
	int			exit_found;

	exit_found = 0;
	collectibles_found = 0;
	data.grid = create_temp_grid(map);
	if (!data.grid)
		return (0);
	data.width = map->width;
	data.height = map->height;
	data.collectibles = &collectibles_found;
	data.exit_found = &exit_found;
	data.total = map->collectibles;
	path_check(&data, map->player_x, map->player_y);
	free_temp_grid(data.grid, map->height);
	return (collectibles_found == map->collectibles && exit_found);
}
