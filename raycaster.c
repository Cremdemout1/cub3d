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

float deg_to_rad(int degree)
{
    return ((float)degree * (M_PI / 180.0f));
}

float   ray_angle(t_game *game, int cur_pixel)
{
    float degree_per_pixel;
    float ray_angle;

    degree_per_pixel = FOV / (float)WIDTH;
    ray_angle = game->map.facing - (FOV / 2) + (degree_per_pixel * (float)cur_pixel); 
    if (ray_angle < 0)
        ray_angle += 360.0f;
    else if (ray_angle > 360.0f) // normalize angle
        ray_angle -= 360.0f; 
    return (ray_angle);
}

void	image_put_pixel(t_img *img, int x, int y, int color)
{
	int	pixel;

	if ((x >= 0 && x < WIDTH) && (y >= 0 && y < HEIGHT))
	{
		pixel = (y * img->line_len) + (x * (img->bits_per_pixel
					/ 8));
		*(unsigned int *)(pixel + img->img_pixel_ptr) = color;
	}
}

float normalize_angle(float angle)
{
    while (angle < 0)
        angle += 360;
    while (angle >= 360)
        angle -= 360;
    return angle;
}

int tex_color(int tex_X, int tex_Y, t_texture *t)
{
    int color;
    int bpp;
    int line_len;

    bpp = t->bpp;
    line_len = t->line_len;
    color = *(int *)&t->addr[(tex_X * (bpp / 8)) + (tex_Y * line_len)];
    return (color);
}

void    draw_wall_column(t_game *game, t_texture *tex, int texPos, int step, int textX, int x)
{
    int y;
    int texY;

    y = 0;
    while (y < HEIGHT)
    {
        if (y < game->wall.top)
            image_put_pixel(&game->img, x, y, rgb_to_color(game->map.ceiling_color));
        else if (y > game->wall.bottom)
            image_put_pixel(&game->img, x, y, rgb_to_color(game->map.floor_color));
        else
        {
            texY = (int)texPos % tex->height;
            texPos += step;
            image_put_pixel(&game->img, x, y, tex_color(textX, texY, tex));
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

void init_player_info(t_game *game)
{
    game->player.posX = game->map.x_player;
    game->player.posY = game->map.y_player;
    game->player.dirX = cos(deg_to_rad(game->map.facing));
    game->player.dirY = sin(deg_to_rad(game->map.facing));
    game->player.planeX = game->player.dirY * 0.66;
    game->player.planeY = -game->player.dirX * 0.66;
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
}

void    determine_height(t_game *game)
{
    game->wall.lineHeight = (int)(HEIGHT / game->ray.perpWallDist);
    game->wall.top = (game->wall.lineHeight * -1) / 2 + HEIGHT / 2;
    if (game->wall.top < 0)
        game->wall.top = 0;
    game->wall.bottom = game->wall.lineHeight / 2 + HEIGHT / 2;
    if (game->wall.bottom >= HEIGHT)
        game->wall.bottom = HEIGHT - 1;

    if (game->ray.side == 0)
        game->wall.wallX = game->player.posY + game->ray.perpWallDist * game->ray.rayDirY;
    else
        game->wall.wallX = game->player.posX + game->ray.perpWallDist * game->ray.rayDirX;
    game->wall.wallX -= floor(game->wall.wallX);
}

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

        int textX = (int)(game->wall.wallX * (double)game->wall.texture->width);
        if (game->ray.side == 0 && game->ray.rayDirX > 0)
            textX = game->wall.texture->width - textX - 1;
        if (game->ray.side == 1 && game->ray.rayDirY < 0)
            textX = game->wall.texture->width - textX - 1; //same????? WHYY

        double step = 1.0 * game->wall.texture->height / game->wall.lineHeight;
        double texPos = (game->wall.top - HEIGHT / 2 + game->wall.lineHeight / 2) * step;

        draw_wall_column(game, game->wall.texture, texPos, step, textX, x);
        x++;
    }

    mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
}



// void    cast_all_rays(t_game *game)
// {
//     //color_background(game);
//     int x = 0;
//     double posX = game->map.x_player;
//     double posY = game->map.y_player;
//     double dirX = cos(deg_to_rad(game->map.facing));
//     double dirY = sin(deg_to_rad(game->map.facing));
//     double planeX = dirY * 0.66;
//     double planeY = -dirX * 0.66;
//     while (x < WIDTH)
//     {
//         double cameraX = 2 * x / (double)WIDTH - 1;
//         double rayDirX = dirX + planeX * cameraX;
//         double rayDirY = dirY + planeY * cameraX;

//         int mapX = (int)posX;
//         int mapY = (int)posY;

//         double sideDistX;
//         double sideDistY;

//         double deltaDistX;
//         double deltaDistY;

//         if (rayDirX == 0)
//             deltaDistX = 1e30;
//         else
//             deltaDistX = fabs(1 / rayDirX);
//         if (rayDirY == 0)
//             deltaDistY = 1e30;
//         else
//             deltaDistY = fabs(1 / rayDirY);
//         int stepX;
//         int stepY;

//         int hit = 0; //was there a wall hit?
//         int side; //is it North or South? East or West?

//         if (rayDirX < 0)
//         {
//             stepX = -1;
//             sideDistX = (posX - mapX) / deltaDistX;
//         }
//         else
//         {
//             stepX = 1;
//             sideDistX = (mapX + 1.0 - posX) * deltaDistX;
//         }
//         if (rayDirY < 0)
//         {
//             stepY = -1;
//             sideDistY = (posY - mapY) * deltaDistY;
//         }
//         else
//         {
//             stepY = 1;
//             sideDistY = (mapY + 1.0 - posY) * deltaDistY;
//         }
//         //cast DDA:
//         while (!hit)
//         {
//             if (sideDistX < sideDistY)
//             {
//                 sideDistX += deltaDistX;
//                 mapX += stepX;
//                 side = 0;
//             }
//             else
//             {
//                 sideDistY += deltaDistY;
//                 mapY += stepY;
//                 side = 1;
//             }
//             if (game->map.map[mapY][mapX] == '1')
//                 hit = 1;
//         }
//         double perpWallDist;
//         if (side == 0)
//             perpWallDist = (sideDistX - deltaDistX);
//         else
//             perpWallDist = (sideDistY - deltaDistY);
//         //draw column of screen
//         int h = HEIGHT;
//         int lineHeight = (int)(h / perpWallDist); //temp fix to make map seem wider
//         int drawStart = -lineHeight / 2 + h / 2;
//         if (drawStart < 0)
//             drawStart = 0;
//         int drawEnd = lineHeight / 2 + h / 2;
//         if (drawEnd >= h)
//             drawEnd = h - 1;

//         double wallX; //calculate where wall was hit
//         if (side == 0)
//             wallX = posY + perpWallDist *rayDirY;
//         else
//             wallX = posX + perpWallDist *rayDirX;
//         wallX -= floor(wallX);

//         //texture coordinate X
//         t_texture *tex;
//         if (side == 0) // Vertical wall
//         {
//             if (rayDirX < 0) // Wall is to the left
//             {
//                 if (game->map.map_start == NORTH || game->map.map_start == SOUTH)
//                     tex = game->texs[3];
//                 else
//                     tex = game->texs[1];
//             }
//             else // Wall is to the right
//             {
//                 if (game->map.map_start == NORTH || game->map.map_start == SOUTH)
//                     tex = game->texs[2];
//                 else
//                     tex = game->texs[0];
//             }
//         }
//         else // Horizontal wall
//         {
//             if (rayDirY < 0) // Wall is above
//             {
//                 if (game->map.map_start == EAST || game->map.map_start == WEST)
//                     tex = game->texs[0];
//                 else
//                     tex = game->texs[3];
//             }
//             else // Wall is below
//             {
//                 if (game->map.map_start == EAST || game->map.map_start == WEST)
//                     tex = game->texs[1];
//                 else
//                     tex = game->texs[2];
//             }
//         }


//         int textX = (int)(wallX * (double)tex->width);
//         if (side == 0 && rayDirX > 0)
//             textX = tex->width - textX - 1;
//         if (side == 1 && rayDirY < 0)
//             textX = tex->width - textX - 1;

//         //texture coordinate Y
//         double step = 1.0 * tex->height / lineHeight;
//         double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;

//         int y = 0;
//         int half = HEIGHT / 2;
//         while (y <= drawStart)
//         {
//             if (y < half)
//                 image_put_pixel(&game->img, x, y, rgb_to_color(game->map.ceiling_color));
//             else
//                 image_put_pixel(&game->img, x, y, rgb_to_color(game->map.floor_color));
//             y++;
//         }
//         while (y <= drawEnd)
//         {
//             int texY = (int)texPos % tex->height;
//             if (texY < 0)
//                 texY += tex->height;
//             texPos += step;
            
//             image_put_pixel(&game->img, x, y, tex_color(textX, texY, tex));
//             y++;
//         }
//         while (y < HEIGHT)
//         {
//             if (y < half)
//                 image_put_pixel(&game->img, x, y, rgb_to_color(game->map.ceiling_color));
//             else
//                 image_put_pixel(&game->img, x, y, rgb_to_color(game->map.floor_color));
//             y++;
//         }
//         x++;
//     }
//     mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
// }
