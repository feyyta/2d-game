/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:14:22 by mcastrat          #+#    #+#             */
/*   Updated: 2025/08/27 14:54:08 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	update_prev_pos(t_game *game)
{
	int	old_x;
	int	old_y;

	old_x = game->map->player_x;
	old_y = game->map->player_y;
	if (old_x == game->map->exit_x && old_y == game->map->exit_y)
		game->map->grid[old_y][old_x] = 'E';
	else
		game->map->grid[old_y][old_x] = '0';
}

static void	handle_collectible(t_game *game, int x, int y)
{
	if (game->map->grid[y][x] == 'C')
	{
		game->map->collected++;
		ft_printf("Collectibles catched (%d), ", game->map->collected);
		if (game->map->collected == game->map->collectibles)
			ft_printf("U catch every collectibles wp! You can exit now!!.\n");
	}
}

static int	is_valid_move(t_game *game, int new_x, int new_y)
{
	char	target_cell;

	if (new_x < 0 || new_x >= game->map->width || new_y < 0
		|| new_y >= game->map->height)
		return (0);
	target_cell = game->map->grid[new_y][new_x];
	if (target_cell == '1')
		return (0);
	if (target_cell == 'E' && game->map->collected < game->map->collectibles)
		return (ft_printf("can t exit! catch every collectibles first\n"), 0);
	return (1);
}

static int	move_player(t_game *game, int new_x, int new_y)
{
	if (!is_valid_move(game, new_x, new_y))
		return (0);
	handle_collectible(game, new_x, new_y);
	update_prev_pos(game);
	game->map->player_x = new_x;
	game->map->player_y = new_y;
	game->moves++;
	game->map->grid[new_y][new_x] = 'P';
	handle_exit(game, new_x, new_y);
	render_game(game);
	print_move_count(game);
	return (1);
}

int	key_press(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	if (game->game_over)
		return (0);
	new_x = game->map->player_x;
	new_y = game->map->player_y;
	if (keycode == ESC_KEY)
		close_game(game);
	else if (keycode == W_KEY || keycode == UP_KEY)
		new_y--;
	else if (keycode == S_KEY || keycode == DOWN_KEY)
		new_y++;
	else if (keycode == A_KEY || keycode == LEFT_KEY)
		new_x--;
	else if (keycode == D_KEY || keycode == RIGHT_KEY)
		new_x++;
	if (new_x != game->map->player_x || new_y != game->map->player_y)
		move_player(game, new_x, new_y);
	return (0);
}
