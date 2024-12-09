/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student->42->fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:35:10 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/01 14:02:55 by ycantin          ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

// void draw_map(t_game *game)
// {
//     int x, y;
//     int map_x, map_y;

//     for (map_y = 0; map_y < game->map.length; map_y++) {
//         for (map_x = 0; map_x < game->map.width[map_y]; map_x++) {
//             if (game->map.map[map_y][map_x] == '1')
//             {
//                 x = map_x * XPM_X;
//                 y = map_y * XPM_Y;
//                 if (game->map.map && game->map.map[map_y][map_x] == '1')
//                     mlx_put_image_to_window(game->scdmlx, game->scdwin, game->texs[0]->img, x, y);  // North wall
//             }
//             else if (map_y == game->map.y_player && map_x == game->map.x_player)
//             {
//                 x = map_x * XPM_X;
//                 y = map_y * XPM_Y;
//                 mlx_put_image_to_window(game->scdmlx, game->scdwin, game->texs[4]->img, x, y);  // North wall
//             }
//         }
//     }
// }