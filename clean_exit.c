
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

void free_resources(t_map *map)
{
    if (map->map)
        free_array(map->map);
    if (map->parser.visited)
        free_bool_array(map->parser.visited, map->length);
    if (map->width)
        free(map->width);
    if (map->texs)
        free_array(map->texs);
    if (map->floor_color)
        free(map->floor_color);
    if (map->ceiling_color)
        free(map->ceiling_color);
}


int destroy(t_game *window)
{
    if (window->win)
    {
        mlx_destroy_window(window->mlx, window->win);
        window->win = NULL;
    }
    if (window->mlx)
    {
        mlx_destroy_display(&window->mlx);
        window->mlx = NULL;
    }
    //free(window->mlx);
    return (0);
}

int exit_t(t_game *g)
{
    free_resources(&g->map);
    free(g);
    exit(0);
    return 1;
}

