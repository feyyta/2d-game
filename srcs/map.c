/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:11:40 by mcastrat          #+#    #+#             */
/*   Updated: 2025/10/01 14:46:49 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

int	check_ext(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".ber", 4) != 0)
		return (ft_printf("Error = Invalid file format need .ber file\n"), 0);
	return (1);
}

static int	get_line_length(char *line)
{
	int	len;

	if (!line)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (len);
}

static int	fill_grid(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		i;
	int		line_len;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 0);
	while (line)
	{
		line_len = get_line_length(line);
		map->grid[i] = malloc(line_len + 1);
		if (!map->grid[i])
			return (get_next_line(-1), free(line), close(fd), 0);
		ft_strlcpy(map->grid[i], line, line_len + 1);
		map->grid[i++][line_len] = '\0';
		free(line);
		line = get_next_line(fd);
	}
	map->grid[i] = NULL;
	return (get_next_line(-1), close(fd), 1);
}

int	get_map_dimensions(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		line_len;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error = file access error\n"), 0);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 0);
	while (line)
	{
		if (map->width == 0)
		{
			line_len = get_line_length(line);
			map->width = line_len;
		}
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 1);
}

int	load_map_data(char *filename, t_map *map)
{
	int	i;

	i = 0;
	ft_bzero(map, sizeof(t_map));
	if (!get_map_dimensions(filename, map))
		return (ft_printf("Error = failed to load dimensions\n"), 0);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (error_map(map, "Error = Memory allocation failed"), 0);
	while (i < map->height + 1)
		map->grid[i++] = NULL;
	if (!fill_grid(filename, map))
		return (error_map(map, "Error = Memory allocation err fill_grid"), 0);
	return (1);
}
