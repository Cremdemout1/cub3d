/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:46:12 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/12 16:59:06 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void center_player_in_tile(t_game *game)
{
    game->player.posX = game->map.x_player + 0.5;
    game->player.posY = game->map.y_player + 0.5;
}

void add_epsilon(t_game *game, char **map, int x, int y)
{
    // printf("x: %d,y: %d\n", x, y);
    if (x + 1 < game->map.width[y] && map[x + 1][y] == '1')
        game->player.posX -= 0.1;
    if (x - 1 >= 1 && map[x - 1][y] == '1') //might have to change to 0
        game->player.posX += 0.1;
    if (y + 1 < game->map.length && map[x][y + 1] == '1')
        game->player.posY -= 0.1;
    if (y - 1 >= 0 && map[x][y - 1] == '1')
        game->player.posY += 0.1;
}

void init_player_info(t_game *game)
{
    center_player_in_tile(game);
    add_epsilon(game, game->map.map, game->map.x_player,game->map.y_player);
    game->player.dirX = cos(deg_to_rad(game->map.facing));
    game->player.dirY = sin(deg_to_rad(game->map.facing));
    game->player.planeX = -game->player.dirY * 0.66;
    game->player.planeY = game->player.dirX * 0.66;
}

void    decide_step(t_game *game)
{
    if (game->ray.rayDirX < 0)
    {
        game->ray.stepX = -1;
        game->ray.sideDistX = (game->player.posX - game->ray.mapX) * game->ray.deltaDistX;
    }
    else
    {
        game->ray.stepX = 1;
        game->ray.sideDistX = (game->ray.mapX + 1.0 - game->player.posX) * game->ray.deltaDistX;
    }
    if (game->ray.rayDirY < 0)
    {
        game->ray.stepY = -1;
        game->ray.sideDistY = (game->player.posY - game->ray.mapY) * game->ray.deltaDistY;
    }
    else
    {
        game->ray.stepY = 1;
        game->ray.sideDistY = (game->ray.mapY + 1.0 - game->player.posY) * game->ray.deltaDistY;
    }
}

void    setup_ray(t_game *game, int x)
{
    game->ray.cameraX = 2 * x / (double)WIDTH - 1;
    game->ray.rayDirX = game->player.dirX + game->player.planeX * game->ray.cameraX;
    game->ray.rayDirY = game->player.dirY + game->player.planeY * game->ray.cameraX;
    
    game->ray.mapX = (int)game->player.posX;
    game->ray.mapY = (int)game->player.posY;

    if (game->ray.rayDirX == 0)
        game->ray.deltaDistX = 1e30;
    else
        game->ray.deltaDistX = fabs(1 / game->ray.rayDirX);
    if (game->ray.rayDirY == 0)
        game->ray.deltaDistY = 1e30;
    else
        game->ray.deltaDistY = fabs(1 / game->ray.rayDirY);
    decide_step(game);
}

void    cast_ray(t_game *game)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (game->ray.sideDistX < game->ray.sideDistY)
        {
            game->ray.sideDistX += game->ray.deltaDistX;
            game->ray.mapX += game->ray.stepX;
            game->ray.side = 0;
        }
        else
        {
            game->ray.sideDistY += game->ray.deltaDistY;
            game->ray.mapY += game->ray.stepY;
            game->ray.side = 1;
        }
        if (game->map.map[game->ray.mapY][game->ray.mapX] == '1')
            hit = 1;
    }
    if (game->ray.side == 0)
        game->ray.perpWallDist = game->ray.sideDistX - game->ray.deltaDistX; //HORIZONTAL WALL
    else
        game->ray.perpWallDist = game->ray.sideDistY - game->ray.deltaDistY; //VERTICAL WALL
    game->ray.hit = hit;
}

void    determine_height(t_game *game)
{
    game->wall.lineHeight = (int)(HEIGHT / game->ray.perpWallDist);
    game->wall.top = (game->wall.lineHeight * -1) / 2 + HEIGHT / 2;
    if (game->wall.top < 0)
        game->wall.top = 0;
    game->wall.bottom = game->wall.top + game->wall.lineHeight;/* game->wall.lineHeight / 2 + HEIGHT / 2; */
    if (game->wall.bottom >= HEIGHT)
        game->wall.bottom = HEIGHT - 1;

    if (game->ray.side == 0)
        game->wall.wallX = game->player.posY + game->ray.perpWallDist * game->ray.rayDirY;
    else
        game->wall.wallX = game->player.posX + game->ray.perpWallDist * game->ray.rayDirX;
    game->wall.wallX -= floor(game->wall.wallX);
}
