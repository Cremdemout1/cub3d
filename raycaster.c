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

void    init_ray(t_ray *ray)
{
    ray->angle = 0;
    ray->distance = -1;
    ray->wall_hit = 0;
    ray->x_hit = -1;
    ray->y_hit = -1;
}

// int get_texture_pixel(t_texture *texture, int x, int y)
// {
//     int offset;
//     char *pixel_addr;

//     offset = (y * texture->line_len) + (x * (texture->bpp / 8));
//     pixel_addr = texture->addr + offset;
//     return (*(int *)pixel_addr);
// }

void draw_wall_column(t_game *game, int x, int wall_top, int wall_bottom, int color)
{
    int y = 0;
    int half = HEIGHT / 2;
    while (y <= wall_top)
    {
        if (y < half)
            image_put_pixel(&game->img, x, y, rgb_to_color(game->map.ceiling_color));
        else
            image_put_pixel(&game->img, x, y, rgb_to_color(game->map.floor_color));
        y++;
    }
    while (y <= wall_bottom)
    {
        image_put_pixel(&game->img, x, y, (unsigned int)color);
        y++;
    }
    while (y < HEIGHT)
    {
        if (y < half)
            image_put_pixel(&game->img, x, y, rgb_to_color(game->map.ceiling_color));
        else
            image_put_pixel(&game->img, x, y, rgb_to_color(game->map.floor_color));
        y++;
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


// void	draw_line_to_image(t_img *img, int x0, int y0, int x1, int y1, int color)
// {
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);
// 	int sx = (x0 < x1) ? 1 : -1;
// 	int sy = (y0 < y1) ? 1 : -1;
// 	int err = dx - dy;

// 	while (1)
// 	{
// 		image_put_pixel(img, x0, y0, color);
// 		if (x0 == x1 && y0 == y1)
// 			break;
// 		int e2 = err * 2;
// 		if (e2 > -dy)
// 		{
// 			err -= dy;
// 			x0 += sx;
// 		}
// 		if (e2 < dx)
// 		{
// 			err += dx;
// 			y0 += sy;
// 		}
// 	}
// }

// void    draw_row_to_img(t_img *img, int y, unsigned int color)
// {
//     int x;
    
//     x = 0;
//     while (x < WIDTH)
//     {
//         image_put_pixel(img, x, y, color);
//         x++;
//     }
// }

// void    color_background(t_game *game)
// {
//     int y;
//     int half;
    
//     y = 0;
//     half = HEIGHT / 2;
//     while (y < half)
//     {
//         draw_row_to_img(&game->img, y, rgb_to_color(game->map.ceiling_color));
//         y++;
//     }
//     while (y < HEIGHT)
//     {
//         draw_row_to_img(&game->img, y, rgb_to_color(game->map.floor_color));
//         y++;
//     }
// }

int tex_color(t_game *game, int tex_X, int tex_Y)
{
    int color;
    int bpp;
    int line_len;
    t_texture *t;

    t = game->texs[0];
    bpp = t->bpp;
    line_len = t->line_len;
    color = *(int *)&t->addr[(tex_X * (bpp / 8)) + (tex_Y * line_len)];
    return (color);
}

void    cast_all_rays(t_game *game)
{
    //color_background(game);
    int x = 0;
    double posX = game->map.x_player;
    double posY = game->map.y_player;
    double dirX = cos(deg_to_rad(game->map.facing));
    double dirY = sin(deg_to_rad(game->map.facing));
    double planeX = dirY * /* tan(FOV / 2) */0.66;
    double planeY = -dirX * /* tan(FOV / 2) */0.66;
    // double time = 0;
    // double oldTimme = 0;
    while (x < WIDTH)
    {
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        int mapX = (int)posX;
        int mapY = (int)posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX;
        double deltaDistY;

        if (rayDirX == 0)
            deltaDistX = 1e30;
        else
            deltaDistX = fabs(1 / rayDirX);
        if (rayDirY == 0)
            deltaDistY = 1e30;
        else
            deltaDistY = fabs(1 / rayDirY);
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side; //is it North or South? East or West?

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) / deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }
        //cast DDA:
        while (!hit)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (game->map.map[mapY][mapX] == '1')
                hit = 1;
        }
        double perpWallDist;
        if (side == 0)
            perpWallDist = (sideDistX - deltaDistX);
        else
            perpWallDist = (sideDistY - deltaDistY);
        //draw column of screen
        int h = HEIGHT;
        int lineHeight = (int)(h / perpWallDist); //temp fix to make map seem wider
        int drawStart = -lineHeight / 2 + h / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + h / 2;
        if (drawEnd >= h)
            drawEnd = h - 1;

        double wallX; //calculate where wall was hit
        if (side == 0)
            wallX = posY + perpWallDist *rayDirY;
        else
            wallX = posX + perpWallDist *rayDirY;
        wallX -= floor(wallX);

        //texture coordinate X
        int textX = (int)(wallX * (double)game->texs[0]->width);
        if (side == 0 && rayDirX > 0)
            textX = game->texs[0]->width - textX - 1;
        if (side == 1 && rayDirY < 0)
            textX = game->texs[0]->width - textX - 1;

        //texture coordinate Y
        double step = 1.0 * game->texs[0]->height / lineHeight;
        double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;



        int y = 0;
        int half = HEIGHT / 2;
        while (y <= drawStart)
        {
            if (y < half)
                image_put_pixel(&game->img, x, y, rgb_to_color(game->map.ceiling_color));
            else
                image_put_pixel(&game->img, x, y, rgb_to_color(game->map.floor_color));
            y++;
        }
        while (y <= drawEnd)
        {
            int texY = (int)texPos % game->texs[0]->height;
            if (texY < 0)
                texY += game->texs[0]->height;
            texPos += step;
            
            image_put_pixel(&game->img, x, y, tex_color(game, textX, texY));
            y++;
        }
        while (y < HEIGHT)
        {
            if (y < half)
                image_put_pixel(&game->img, x, y, rgb_to_color(game->map.ceiling_color));
            else
                image_put_pixel(&game->img, x, y, rgb_to_color(game->map.floor_color));
            y++;
        }
        //int color;
        // if (side == 1)
        //     color = 0xff005f; // magenta
        // else
        //     color = 0x00ffff; //light blue
        // draw_wall_column(game, x, drawStart, drawEnd, color);
        //draw_wall_column(game, x, drawStart, drawEnd, color);
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
}
