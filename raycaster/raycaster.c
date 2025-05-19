/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:49:35 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 18:02:44 by ycantin          ###   ########.fr       */
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
