/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:37:26 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 17:50:27 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H
# include "main.h"
# include "structs.h"

void	init_player_info(t_game *game);
void	decide_step(t_game *game);
void	setup_ray(t_game *game, int x);
void	cast_ray(t_game *game);
void	determine_height(t_game *game);
void	draw_wall_column(t_game *game, int x);
void	select_texture(t_game *game);

#endif