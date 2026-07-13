/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-08-28 22:31:43 by mcastrat          #+#    #+#             */
/*   Updated: 2025-08-28 22:31:43 by mcastrat         ###   ########i         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

void	free_temp_grid(char **temp_grid, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(temp_grid[i]);
		i++;
	}
	free(temp_grid);
}

void	print_move_count(t_game *game)
{
	char	*move_str;

	move_str = ft_itoa(game->moves);
	if (move_str)
	{
		ft_printf("U moved %s time\n", move_str);
		free(move_str);
	}
}

void	handle_exit(t_game *game, int x, int y)
{
	if (x == game->map->exit_x && y == game->map->exit_y
		&& game->map->collected == game->map->collectibles)
	{
		ft_printf("GG WP\n");
		ft_printf("U ended the game with %d moves , try again and do better!\n",
			game->moves);
		game->game_over = 1;
		close_game(game);
	}
}
