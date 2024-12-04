/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:35 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/01 04:28:29 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int keybrd_hook(int key, t_game **game)
{
    float new_x = (*game)->map.x_player;
    float new_y = (*game)->map.y_player;

    // Movement calculations based on input
    if (key == XK_W)
        new_y += PLAYER_SPEED;
    else if (key == XK_S)
        new_y -= PLAYER_SPEED;
    else if (key == XK_A)
        new_x += PLAYER_SPEED;
    else if (key == XK_D)
        new_x -= PLAYER_SPEED;
    else if (key == XK_ESCAPE)
        exit_t((*game));

    int map_width = (*game)->map.width[(int)new_y] * XPM_X; // Map's total width
    int map_height = (*game)->map.length * XPM_Y;      // Map's total height
    
    if (new_x >= 0 && new_x < map_width &&new_y >= 0 && new_y < map_height)
    {
        (*game)->map.x_player = new_x;
        (*game)->map.y_player = new_y;
        cast_all_rays(*game);
    }
    return (key);
}
