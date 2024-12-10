/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:50:23 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/10 17:32:20 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void    draw_wall_column(t_game *game, int x)
{
    int y;
    int texY;

    y = 0;
    texY = 0;
    while (y < HEIGHT)
    {
        if (y < game->wall.top)
            image_put_pixel(&game->img, x, y, rgb_to_color(game->map.ceiling_color));
        else if (y > game->wall.bottom)
            image_put_pixel(&game->img, x, y, rgb_to_color(game->map.floor_color));
        else
        {
            texY = (int)game->wall.texture_pos % game->wall.texture->height;
            if (texY < 0)
                texY += game->wall.texture->height;
            game->wall.texture_pos += game->wall.t_step;
            image_put_pixel(&game->img, x, y,
                tex_color(game->wall.textureX, texY, game->wall.texture));
        }
        y++;
    }
}

void    select_texture(t_game *game)
{
    if (game->ray.side == 0) // Vertical wall
    {
        if (game->ray.rayDirX < 0) // Wall is to the left
        {
            if (game->map.map_start == NORTH || game->map.map_start == SOUTH)
                game->wall.texture = game->texs[3];
            else
                game->wall.texture = game->texs[1];
        }
        else // Wall is to the right
        {
            if (game->map.map_start == NORTH || game->map.map_start == SOUTH)
                game->wall.texture = game->texs[2];
            else
                game->wall.texture = game->texs[0];
        }
    }
    else // Horizontal wall
    {
        if (game->ray.rayDirY < 0) // Wall is above
        {
            if (game->map.map_start == EAST || game->map.map_start == WEST)
                game->wall.texture = game->texs[0];
            else
                game->wall.texture = game->texs[3];
        }
        else // Wall is below
        {
            if (game->map.map_start == EAST || game->map.map_start == WEST)
                game->wall.texture = game->texs[1];
            else
                game->wall.texture = game->texs[2];
        }
    }
}

float deg_to_rad(int degree)
{
    return ((float)degree * (M_PI / 180.0f));
}


float normalize_angle(float angle)
{
    while (angle < 0)
        angle += 360;
    while (angle >= 360)
        angle -= 360;
    return angle;
}
