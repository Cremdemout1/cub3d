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

// void    init_ray_holder(t_ray_holder *ray, t_game *game, float ray_angle)
// {
//     ray->delta_x = cos(deg_to_rad(ray_angle));
//     ray->delta_y = sin(deg_to_rad(ray_angle));
//     ray->start_x = game->map.x_player;
//     ray->start_y = game->map.y_player;
//     ray->step_x = ray->delta_x * XPM_X;
//     ray->step_y = ray->delta_y * XPM_Y;
//     ray->cur_x = ray->start_x;
//     ray->cur_y = ray->start_y;
//     // ray->grid_x = (int) ray->cur_x / XPM_X;
//     // ray->grid_y = (int) ray->cur_y / XPM_Y;
//     ray->grid_x = ray->start_x;
//     ray->grid_y = ray->start_y;
// }

// e

void    init_ray(t_ray *ray)
{
    ray->angle = 0;
    ray->distance = -1;
    ray->wall_hit = 0;
    ray->x_hit = -1;
    ray->y_hit = -1;
}

void draw_wall_column(t_img *img, int x, int wall_top, int wall_bottom, int color)
{
    int y = wall_top;
    while (y <= wall_bottom)
    {
        image_put_pixel(img, x, y, color);
        y++;
    }
}

// t_ray cast_ray(t_game *game, float ray_angle)
// {
//     t_ray ray;
//     t_ray_holder holder;

//     init_ray(&ray);
//     ray.angle = ray_angle;
//     init_ray_holder(&holder, game, ray.angle);

//     printf("Ray Angle: %f degrees\n", ray_angle);

//     while (holder.cur_x >= 0 && holder.cur_x < game->map.biggest_width &&
//            holder.cur_y >= 0 && holder.cur_y < game->map.length)
//     {
//         // Convert ray's current position to grid coordinates
//         holder.grid_x = (int)(holder.cur_x / XPM_X);
//         holder.grid_y = (int)(holder.cur_y / XPM_Y);

//         printf("Current Position: (%f, %f)\n", holder.cur_x, holder.cur_y);
//         printf("Current Grid: (%d, %d)\n", holder.grid_x, holder.grid_y);

//         // Check if the ray hit a wall
//         if (game->map.map[holder.grid_y][holder.grid_x] == '1')
//         {
//             ray.wall_hit = 1;
//             ray.x_hit = holder.cur_x;
//             ray.y_hit = holder.cur_y;
//             ray.distance = sqrt(pow(holder.cur_x - holder.start_x, 2) +
//                                 pow(holder.cur_y - holder.start_y, 2));
//             printf("Wall Hit at Grid (%d, %d), World Position (%f, %f)\n",
//                    holder.grid_x, holder.grid_y, ray.x_hit, ray.y_hit);
//             printf("Distance to Wall: %f\n", ray.distance);
//             break;
//         }

//         // Step the ray to the next horizontal or vertical intersection
//         if (holder.hor_step < holder.ver_step)
//         {
//             holder.cur_x += holder.hor_step * holder.step_x;
//             holder.cur_y += holder.hor_step * holder.delta_y;
//             holder.hor_step += XPM_X / fabs(holder.delta_x);
//         }
//         else
//         {
//             holder.cur_x += holder.ver_step * holder.delta_x;
//             holder.cur_y += holder.ver_step * holder.step_y;
//             holder.ver_step += XPM_Y / fabs(holder.delta_y);
//         }

//         printf("Next Intersection: hor_step=%d, ver_step=%d\n",
//                holder.hor_step, holder.ver_step);
//     }

//     if (!ray.wall_hit)
//     {
//         printf("Ray did not hit a wall within map bounds.\n");
//     }

//     return ray;
// }

float normalize_angle(float angle)
{
    while (angle < 0)
        angle += 360;
    while (angle >= 360)
        angle -= 360;
    return angle;
}


void	draw_line_to_image(t_img *img, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		image_put_pixel(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = err * 2;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void	update_image(t_game *game)
{
	// Destroy the previous image
	if (game->img_ptr)
		mlx_destroy_image(game->mlx, game->img_ptr);

	// Create a new image
	game->img_ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->img.img_addr = mlx_get_data_addr(game->img_ptr, 
                                       &game->img.bits_per_pixel, 
                                       &game->img.line_len, 
                                       &game->img.endian);
    if (!game->img.img_addr)
    {
        ft_printf_fd(2, "Failed to get image address\n");
        return;
    }
}

// void cast_all_rays(t_game *game)
// {
//     int i;
//     t_ray ray;
//     float wall_height, wall_top, wall_bottom;

//     update_image(game); // Ensure the frame buffer is clean for rendering
//     for (i = 0; i < WIDTH; i++)
//     {
//         ray.angle = /* normalize_angle */(ray_angle(game, i));
//         float player_fov_start = normalize_angle(game->map.facing - FOV / 2);
//         float player_fov_end = normalize_angle(game->map.facing + FOV / 2);
//         if ((player_fov_start < player_fov_end &&
//              ray.angle >= player_fov_start && ray.angle <= player_fov_end) ||
//             (player_fov_start > player_fov_end &&
//              (ray.angle >= player_fov_start || ray.angle <= player_fov_end)))
//         {
//             ray = cast_ray(game, ray.angle);
//             if (ray.wall_hit)
//             {
//                 float corrected_distance = ray.distance * cos(deg_to_rad(ray.angle - game->map.facing));
//                 wall_height = (XPM_X * (WIDTH / 2.0) / tan(deg_to_rad(FOV / 2))) / corrected_distance;
//                 wall_height /= 2;
//                 wall_top = (HEIGHT / 2.0) - (wall_height / 2.0);
//                 wall_bottom = wall_top + wall_height;
//                 int color = 0x0000FF;
//                 draw_wall_column(&game->img, i, (int)wall_top, (int)wall_bottom, color);
//             }
//         }
//     }
//     mlx_put_image_to_window(game->mlx, game->win, game->img_ptr, 0, 0);
// }

void    cast_all_rays(t_game *game)
{
    double posX = game->map.x_player;
    double posY = game->map.y_player;

    double dirX = -1;
    double dirY = 0;
    double planeX = 0;
    double planeY = 0.66;
    double time = 0;
    double oldTime = 0;
    int x = 0;
    while (x < WIDTH)
    {
        double cameraX = 2 * x / (double)WIDTH - 1;
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        double sideDistX;
        double sideDistY;

        double deltaDistX;
        double deltaDistY;
        if (rayDirX == 0)
            deltaDistX = 1e30;
        else
            deltaDistX = abs(1 / rayDirX);
        if (rayDirY == 0)
            deltaDistY = 1e30;
        else
            deltaDistY = abs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;
        int hit = 0; // was wall hit?
        int side; // is it NS or EW?

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - Ma)
        }
        x++;
    }
}
