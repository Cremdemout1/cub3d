/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:43:03 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 17:48:29 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	move_player_by_direction(t_game *game, double dx,
	double dy, double speed_multiplier)
{
	double	next_x;
	double	next_y;

	next_x = game->player.pos_x + dx
		* PLAYER_SPEED * speed_multiplier * game->dt;
	next_y = game->player.pos_y + dy
		* PLAYER_SPEED * speed_multiplier * game->dt;
	change_player_coords(game, next_x, next_y);
	cast_all_rays(game);
}

void	assign_potential_coords(t_variables *p, double x, double y)
{
	p->pr_min_x = (int)(x - PLAYER_RADIUS);
	p->pr_min_y = (int)(y - PLAYER_RADIUS);
	p->pr_plus_x = (int)(x + PLAYER_RADIUS);
	p->pr_plus_y = (int)(y + PLAYER_RADIUS);
}

void	prep_rotation(t_game *game, double rot_speed)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = game->player.dir_x;
	oldplane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x
		* cos(-rot_speed) - game->player.dir_y * sin(-rot_speed);
	game->player.dir_y = olddir_x
		* sin(-rot_speed) + game->player.dir_y * cos(-rot_speed);
	game->player.plane_x = oldplane_x
		* cos(-rot_speed) - game->player.plane_y * sin(-rot_speed);
	game->player.plane_y = oldplane_x
		* sin(-rot_speed) + game->player.plane_y * cos(-rot_speed);
}
