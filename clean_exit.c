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

void free_textures(t_texture **textures, int count, void *mlx)
{
    int i;

    i = 0;
    while (i < count)
    {
        if (textures[i])
        {
            if (textures[i]->img)
                mlx_destroy_image(mlx, textures[i]->img);
            free(textures[i++]);
        }
    }
    free(textures);
}

void free_resources(t_game **game)
{
    if ((*game) && (*game)->map.map)
        free_array((*game)->map.map);
    if ((*game)->map.parser.visited)
        free_bool_array((*game)->map.parser.visited, (*game)->map.length);
    if ((*game)->map.width)
        free((*game)->map.width);
    if ((*game)->map.texs)
        free_array((*game)->map.texs);
    if((*game)->texs)
        free_textures((*game)->texs, 5, (*game)->mlx);
    if ((*game)->map.floor_color)
        free((*game)->map.floor_color);
    if ((*game)->map.ceiling_color)
        free((*game)->map.ceiling_color);
}

int exit_t(t_game *g)
{
    free_resources(&g);
    if (g->img_ptr)
        mlx_destroy_image(g->mlx, g->img_ptr);
    if (g->win)
        mlx_destroy_window(g->mlx, g->win);
    if (g->mlx)
    {
        mlx_do_key_autorepeaton(g->mlx);
        mlx_destroy_display(g->mlx);
        free(g->mlx);
    }
    free(g);
    exit(0);
}

int exit_x_button(void *param)
{
    t_game *g;
 
    g = (t_game *)param;
    (void)param;
    free_resources(&g);
    if (g->img_ptr)
        mlx_destroy_image(g->mlx, g->img_ptr);
    if (g->win)
        mlx_destroy_window(g->mlx, g->win);
    if (g->mlx)
    {
        mlx_do_key_autorepeaton(g->mlx);
        mlx_destroy_display(g->mlx);
        free(g->mlx);
    }
    free(g);
    exit(0);
}


