/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:49:35 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/21 16:49:33 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	cast_all_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		setup_ray(game, x);
		cast_ray(game);
		determine_height(game);
		select_texture(game);
		game->wall.texture_x = (game->wall.wall_x
				* (double)game->wall.texture->width);
		if (game->ray.side == 0 && game->ray.raydir_x > 0)
			game->wall.texture_x = game->wall.texture->width
				- game->wall.texture_x - 1;
		if (game->ray.side == 1 && game->ray.raydir_y < 0)
			game->wall.texture_x = game->wall.texture->width
				- game->wall.texture_x - 1;
		game->wall.t_step = 1.0 * game->wall.texture->height
			/ game->wall.line_height;
		game->wall.texture_pos = (game->wall.top
				- HEIGHT / 2 + game->wall.line_height / 2) * game->wall.t_step;
		draw_wall_column(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
}

void	cast_ray(t_game *game)
{
	int		hit;
	char	cell;

	hit = 0;
	while (!hit)
	{
		dda(game, &hit);
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
