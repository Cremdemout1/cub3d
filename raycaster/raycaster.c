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

#include "../includes/main.h"

void cast_all_rays(t_game *game)
{
    int x;
    
    x = 0;
    init_player_info(game);
    while (x < WIDTH)
    {
        setup_ray(game, x);
        cast_ray(game);
        determine_height(game);
        select_texture(game);
        game->wall.textureX = (game->wall.wallX * (double)game->wall.texture->width);
        if (game->ray.side == 0 && game->ray.rayDirX > 0)
            game->wall.textureX = game->wall.texture->width - game->wall.textureX - 1;
        if (game->ray.side == 1 && game->ray.rayDirY < 0)
            game->wall.textureX = game->wall.texture->width - game->wall.textureX - 1;
        game->wall.t_step = 1.0 * game->wall.texture->height / game->wall.lineHeight;
        game->wall.texture_pos = (game->wall.top -
            HEIGHT / 2 + game->wall.lineHeight / 2) * game->wall.t_step;
        draw_wall_column(game, x);
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
}
