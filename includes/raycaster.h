/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:49 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/10 17:32:23 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
#define RAYCASTER_H
#include "main.h"
#include "structs.h"

void    init_player_info(t_game *game);
void    decide_step(t_game *game);
void    setup_ray(t_game *game, int x);
void    cast_ray(t_game *game);
void    determine_height(t_game *game);
void    draw_wall_column(t_game *game, int x);
void    select_texture(t_game *game);

float   normalize_angle(float angle);


#endif