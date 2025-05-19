/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:55:43 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 18:00:34 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	center_player_in_tile(t_game *game)
{
	game->player.pos_x = game->map.x_player + 0.5;
	game->player.pos_y = game->map.y_player + 0.5;
}

void	init_player_info(t_game *game)
{
	center_player_in_tile(game);
	game->player.dir_x = cos(deg_to_rad(game->map.facing));
	game->player.dir_y = sin(deg_to_rad(game->map.facing));
	game->player.plane_x = -game->player.dir_y * 0.66;
	game->player.plane_y = game->player.dir_x * 0.66;
}

void	decide_step(t_game *game)
{
	if (game->ray.raydir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.side_dist_x = (game->player.pos_x - game->ray.map_x)
			*game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.side_dist_x = (game->ray.map_x + 1.0 - game->player.pos_x)
			* game->ray.delta_dist_x;
	}
	if (game->ray.raydir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.side_dist_y = (game->player.pos_y - game->ray.map_y)
			* game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.side_dist_y = (game->ray.map_y + 1.0 - game->player.pos_y)
			* game->ray.delta_dist_y;
	}
}

void	setup_ray(t_game *game, int x)
{
	game->ray.camera_x = 2 * x / (double)WIDTH - 1;
	game->ray.raydir_x = game->player.dir_x
		+ game->player.plane_x * game->ray.camera_x;
	game->ray.raydir_y = game->player.dir_y
		+ game->player.plane_y * game->ray.camera_x;
	game->ray.map_x = (int)game->player.pos_x;
	game->ray.map_y = (int)game->player.pos_y;
	if (game->ray.raydir_x == 0)
		game->ray.delta_dist_x = 1e30;
	else
		game->ray.delta_dist_x = fabs(1 / game->ray.raydir_x);
	if (game->ray.raydir_y == 0)
		game->ray.delta_dist_y = 1e30;
	else
		game->ray.delta_dist_y = fabs(1 / game->ray.raydir_y);
	decide_step(game);
}

void	cast_ray(t_game *game)
{
	int		hit;
	char	cell;

	hit = 0;
	while (!hit)
	{
		if (game->ray.side_dist_x < game->ray.side_dist_y)
		{
			game->ray.side_dist_x += game->ray.delta_dist_x;
			game->ray.map_x += game->ray.step_x;
			game->ray.side = 0;
		}
		else
		{
			game->ray.side_dist_y += game->ray.delta_dist_y;
			game->ray.map_y += game->ray.step_y;
			game->ray.side = 1;
		}
		if (game->ray.map_y < 0 || game->ray.map_y >= game->map.length
			|| game->ray.map_x < 0 || game->ray.map_x >= game->map.max_width)
		{
			hit = 1;
			break ;
		}
		cell = game->map.map[game->ray.map_y][game->ray.map_x];
		if (game->ray.map_y >= 0 && game->ray.map_y < game->map.length
			&& game->ray.map_x >= 0 && game->ray.map_x
			< game->map.width[game->ray.map_y]
			&& game->map.map[game->ray.map_y] && cell == '1')
			hit = 1;
	}
	if (game->ray.side == 0)
		game->ray.perp_wall_dist = game->ray.side_dist_x
			- game->ray.delta_dist_x;
	else
		game->ray.perp_wall_dist = game->ray.side_dist_y
			- game->ray.delta_dist_y;
	game->ray.hit = hit;
}

void	determine_height(t_game *game)
{
	game->wall.line_height = (int)(HEIGHT / game->ray.perp_wall_dist);
	game->wall.top = (game->wall.line_height * -1) / 2 + HEIGHT / 2;
	if (game->wall.top < 0)
		game->wall.top = 0;
	game->wall.bottom = game->wall.top + game->wall.line_height;
	if (game->wall.bottom >= HEIGHT)
		game->wall.bottom = HEIGHT - 1;
	if (game->ray.side == 0)
		game->wall.wall_x = game->player.pos_y
			+ game->ray.perp_wall_dist * game->ray.raydir_y;
	else
		game->wall.wall_x = game->player.pos_x
			+ game->ray.perp_wall_dist * game->ray.raydir_x;
	game->wall.wall_x -= floor(game->wall.wall_x);
}
