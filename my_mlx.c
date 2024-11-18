/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:35:10 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/06 08:38:26 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

// int x_button(t_window *window)
// {
//     // if (g->window.win)
//     // {
//     //     mlx_destroy_window(g->window.mlx, g->window.win);
//     //     g->window.win = NULL;
//     // }
//     if (window->mlx)
//     {
//         mlx_destroy_display(window->mlx);
//         window->mlx = NULL;
//     }
//     return (0);
// }

void    loop(t_game *g)
{
    if (g->mlx)
        mlx_loop(g->mlx);
}

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}