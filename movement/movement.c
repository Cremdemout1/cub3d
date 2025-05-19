/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:29:54 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 17:48:26 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	player_rotate(t_game *game)
{
	double	rot_speed;

	rot_speed = ROT_SPEED * game->dt;
	if (game->keys[LEFT_ARR])
	{
		prep_rotation(game, rot_speed);
		cast_all_rays(game);
	}
	if (game->keys[RIGHT_ARR])
	{
		prep_rotation(game, -rot_speed);
		cast_all_rays(game);
	}
}

int	check_collision(t_game *game, double x, double y)
{
	t_variables	p;

	assign_potential_coords(&p, x, y);
	if ((int)y < 0 || (int)y >= game->map.length)
		return (1);
	if (p.pr_min_x < 0 || p.pr_plus_x
		>= (int)ft_strlen(game->map.map[(int)y]))
		return (1);
	if (p.pr_min_y < 0 || p.pr_plus_y >= game->map.length)
		return (1);
	if ((int)x >= (int)ft_strlen(game->map.map[p.pr_plus_y])
		|| (int)x >= (int)ft_strlen(game->map.map[p.pr_min_y]))
		return (1);
	if (game->map.map[(int)y][p.pr_plus_x] == '1'
		|| game->map.map[(int)y][p.pr_min_x] == '1'
		|| game->map.map[p.pr_plus_y][(int)x] == '1'
		|| game->map.map[p.pr_min_y][(int)x] == '1')
		return (1);
	if (game->map.map[p.pr_plus_y][p.pr_plus_x] == '1' ||
		game->map.map[p.pr_min_y][p.pr_min_x] == '1' ||
		game->map.map[p.pr_plus_y][p.pr_plus_x] == '1' ||
		game->map.map[p.pr_min_y][p.pr_min_x] == '1')
		return (1);
	return (0);
}

void	change_player_coords(t_game *game, double nextX, double nextY)
{
	if (!check_collision(game, nextX, nextY))
	{
		game->player.pos_x = nextX;
		game->player.pos_y = nextY;
	}
}
// sliding very rarely gives seg fault in corners when using valgrind
// else 
	// {
	//	 if (!check_collision(game, nextX, game->player.pos_y))
	//		 game->player.pos_x = nextX;
	//	 if (!check_collision(game, game->player.pos_x, nextY))
	//		 game->player.pos_y = nextY;
	// }

void	player_move(t_game *game)
{
	if (game->keys[119])
		move_player_by_direction(game, game->player.dir_x,
			game->player.dir_y, 1.0);
	if (game->keys[115])
		move_player_by_direction(game, -game->player.dir_x,
			-game->player.dir_y, 1.0);
	if (game->keys[100])
		move_player_by_direction(game, -game->player.dir_y,
			game->player.dir_x, 2.0 / 3.0);
	if (game->keys[97])
		move_player_by_direction(game, game->player.dir_y,
			-game->player.dir_x, 2.0 / 3.0);
}
