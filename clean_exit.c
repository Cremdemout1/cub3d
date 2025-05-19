/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:42:34 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 15:43:31 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void	free_textures(t_texture **textures, int count, void *mlx)
{
	int	i;

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

void	free_resources(t_game **game)
{
	if ((*game) && (*game)->map.map)
		free_array((*game)->map.map);
	if ((*game)->map.parser.visited)
		free_bool_array((*game)->map.parser.visited, (*game)->map.length);
	if ((*game)->map.width)
		free((*game)->map.width);
	if ((*game)->map.texs)
		free_array((*game)->map.texs);
	if ((*game)->texs)
		free_textures((*game)->texs, 5, (*game)->mlx);
	if ((*game)->map.floor_color)
		free((*game)->map.floor_color);
	if ((*game)->map.ceiling_color)
		free((*game)->map.ceiling_color);
}

void	game_error(t_game **g)
{
	if (*g && (*g)->map.map)
		free_array((*g)->map.map);
	if ((*g)->map.parser.visited)
		free_bool_array((*g)->map.parser.visited, (*g)->map.length);
	if ((*g)->map.width)
		free((*g)->map.width);
	if ((*g)->map.floor_color)
		free((*g)->map.floor_color);
	if ((*g)->map.ceiling_color)
		free((*g)->map.ceiling_color);
	if ((*g)->map.texs)
		free_array((*g)->map.texs);
	if ((*g)->win)
		mlx_destroy_window((*g)->mlx, (*g)->win);
	if ((*g)->mlx)
	{
		mlx_do_key_autorepeaton((*g)->mlx);
		mlx_destroy_display((*g)->mlx);
		free((*g)->mlx);
	}
	free(*g);
}

int	exit_x_button(void *param)
{
	t_game	*g;

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
