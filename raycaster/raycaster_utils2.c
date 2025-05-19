/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:49:59 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 18:01:08 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	draw_wall_column(t_game *game, int x)
{
	int	y;
	int	tex_y;

	y = 0;
	tex_y = 0;
	while (y < HEIGHT)
	{
		if (y < game->wall.top)
			image_put_pixel(&game->img, x, y,
				rgb_to_color(game->map.ceiling_color));
		else if (y > game->wall.bottom)
			image_put_pixel(&game->img, x, y,
				rgb_to_color(game->map.floor_color));
		else
		{
			tex_y = (int)game->wall.texture_pos % game->wall.texture->height;
			if (tex_y < 0)
				tex_y += game->wall.texture->height;
			game->wall.texture_pos += game->wall.t_step;
			image_put_pixel(&game->img, x, y,
				tex_color(game->wall.texture_x, tex_y, game->wall.texture));
		}
		y++;
	}
}

// if side == 0, vertical wall
	// if raydir_x < 0, wall is to the left ELSE right
// if side == 1, horizontal wall
	// if raydir_y < 0, wall is above ELSE below

void	select_texture(t_game *game)
{
	if (game->ray.side == 0)
	{
		if (game->ray.raydir_x < 0)
		{
			if (game->map.map_start == NORTH || game->map.map_start == SOUTH)
				game->wall.texture = game->texs[3];
			else
				game->wall.texture = game->texs[1];
		}
		else
		{
			if (game->map.map_start == NORTH || game->map.map_start == SOUTH)
				game->wall.texture = game->texs[2];
			else
				game->wall.texture = game->texs[0];
		}
	}
	else
	{
		if (game->ray.raydir_y < 0)
		{
			if (game->map.map_start == EAST || game->map.map_start == WEST)
				game->wall.texture = game->texs[0];
			else
				game->wall.texture = game->texs[3];
		}
		else
		{
			if (game->map.map_start == EAST || game->map.map_start == WEST)
				game->wall.texture = game->texs[1];
			else
				game->wall.texture = game->texs[2];
		}
	}
}

float	deg_to_rad(int degree)
{
	return ((float)degree * (M_PI / 180.0f));
}
