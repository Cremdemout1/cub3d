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
    ray_angle = game->map.facing - (FOV / 2) + degree_per_pixel + (float)cur_pixel; 
    if (ray_angle < 0)
        ray_angle += 360.0f;
    else if (ray_angle > 360.0f) // normalize angle
        ray_angle -= 360.0f; 
    return (ray_angle);
}

void    init_ray_holder(t_ray_holder *ray, t_game *game, float ray_angle)
{
    ray->delta_x = cos(deg_to_rad(ray_angle));
    ray->delta_y = sin(deg_to_rad(ray_angle));
    ray->start_x = game->map.x_player;
    ray->start_y = game->map.y_player;
    ray->step_x = ray->delta_x * XPM_X;
    ray->step_y = ray->delta_y * XPM_Y;
    ray->cur_x = ray->start_x;
    ray->cur_y = ray->start_y;
    ray->grid_x = (int) ray->cur_x / XPM_X;
    ray->grid_y = (int) ray->cur_y / XPM_Y;
}

// t_ray    *cast_ray(t_game *game, int x_for_angle)
// {
//     t_ray *ray;
//     t_ray_holder holder;

//     ray = malloc (sizeof (t_ray));
//     if (!ray)
//         return (NULL);
//     init_ray_holder(&holder, game);
//     ray->angle = ray_angle(game, x_for_angle);
//     while (holder.cur_x >= 0 && holder.cur_x < game->map.width[holder.grid_y]
//         && holder.cur_y >= 0 && holder.cur_y < game->map.length)
//     {
//         if (game->map.map[holder.grid_y][holder.grid_x] == '1')
//         {
//             ray->wall_hit = 1;
//             ray->x_hit = holder.cur_x;
//             ray->y_hit = holder.cur_y;
//             ray->distance = sqrtf(powf((holder.cur_x - holder.start_x), 2)
//                 + powf((holder.cur_y - holder.start_y), 2));
//             break ;
//         }
//         holder.cur_x += holder.step_x;
//         holder.cur_y += holder.step_y;
//         holder.grid_x = (int)(holder.cur_x / XPM_X);
//         holder.grid_y = (int)(holder.cur_y / XPM_Y);
//     }
//     return (ray);
// }

t_ray *cast_ray(t_game *game, int x_for_angle)
{
    t_ray *ray;
    t_ray_holder holder;

    // Allocate memory for the ray
    ray = malloc(sizeof(t_ray));
    if (!ray)
        return (NULL);

    // Set the angle for the current ray
    ray->angle = ray_angle(game, x_for_angle);
    printf("ANGLE:  %f\n", ray->angle);
    init_ray_holder(&holder, game, ray->angle);
    // // Print the initial values of the holder for debugging
    // printf("Initial holder values: \n");
    // printf("start_x: %f, start_y: %f, cur_x: %f, cur_y: %f\n", 
    //         holder.start_x, holder.start_y, holder.cur_x, holder.cur_y);
    // printf("grid_x: %d, grid_y: %d\n", holder.grid_x, holder.grid_y);
    // printf("delta_x: %f, delta_y: %f\n", holder.delta_x, holder.delta_y);
    // printf("step_x: %f, step_y: %f\n", holder.step_x, holder.step_y);

    // Cast the ray and check for wall hits
    while (holder.cur_x >= 0 && holder.cur_x < game->map.width[holder.grid_y]
        && holder.cur_y >= 0 && holder.cur_y < game->map.length)
    {
        // Print the values of the holder during each step of the raycasting process
        printf("Iteration: cur_x = %f, cur_y = %f, grid_x = %d, grid_y = %d\n", 
                    holder.cur_x, holder.cur_y, holder.grid_x, holder.grid_y);
        // Check if we've hit a wall
        if (game->map.map[holder.grid_y][holder.grid_x] == '1')
        {
            ray->wall_hit = 1;
            ray->x_hit = holder.cur_x;
            ray->y_hit = holder.cur_y;
            // ray->distance = sqrtf(powf((holder.cur_x - holder.start_x), 2)
            //     + powf((holder.cur_y - holder.start_y), 2));
            ray->distance = fabs(holder.cur_x - holder.start_x) + fabs(holder.cur_y - holder.start_y);
            printf("im outta here\n");
            break;
        }

        // Update the ray's position
        holder.cur_x += holder.step_x;
        holder.cur_y += holder.step_y;

        // Update the grid cell we are checking
        holder.grid_x = (int)(holder.cur_x / XPM_X);
        holder.grid_y = (int)(holder.cur_y / XPM_Y);

        // Optional: Add a limit on the maximum distance the ray can travel
        if (ray->distance > 1000)
            break;
    }

    return (ray);
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        mlx_pixel_put(game->mlx, game->win, x0, y0, color);

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

void    cast_all_rays(t_game *game)
{
    int i;
    t_ray **all_rays;

    i = 0;
    all_rays = malloc(sizeof (t_ray *) * WIDTH);
    if (!all_rays)
        return ;
    while (i < WIDTH)
    {
        all_rays[i] = cast_ray(game, i);
        if (all_rays[i]->wall_hit)
        {
            // Draw the ray as a line from the player to the hit point
            draw_line(game, (int)game->map.x_player, (int)game->map.y_player, 
                      (int)all_rays[i]->x_hit, (int)all_rays[i]->y_hit, 0xFF0000);  // Red color
        }
        printf("ray[%d] distance : %f\n", i, all_rays[i]->distance);
        free(all_rays[i]);  // Free the ray after use
        i++;
    }
    free(all_rays);
}
