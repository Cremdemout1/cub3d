/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:35:10 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/07 18:45:11 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	img_placeholder(t_game **game)
{
	(*game)->img.bits_per_pixel = 32;
	(*game)->img.line_len = WIDTH * 4;
	(*game)->img.endian = 0;
	(*game)->img_ptr = mlx_new_image((*game)->mlx, WIDTH, HEIGHT);
	(*game)->img.img_pixel_ptr = mlx_get_data_addr((*game)->img_ptr,
			&(*game)->img.bits_per_pixel, &(*game)->img.line_len,
			&(*game)->img.endian);
}

int keybrd_hook(int key, t_game **game)
{
    if (key == 65307)
        exit_x_button((void *)*game);
    if (key == 65361)
        (*game)->keys[LEFT_ARR] = true;
    else if (key == 65363)
        (*game)->keys[RIGHT_ARR] = true;
    else if (key >= 0 && key < 280)
        (*game)->keys[key] = true;
    return key;
}

int keyrelease_hook(int key, t_game **game)
{
    if (key == 65361)
        (*game)->keys[LEFT_ARR] = false;
    else if (key == 65363)
        (*game)->keys[RIGHT_ARR] = false;
    if (key >= 0 && key < 280)
        (*game)->keys[key] = false;
    return key;
}


int all_moves(t_game **game, int keycode)
{
    update_dt(*game);
    if ((*game)->keys[119] || (*game)->keys[115]
        || (*game)->keys[100] || (*game)->keys[97])
        player_move(*game);
    if ((*game)->keys[LEFT_ARR] || (*game)->keys[RIGHT_ARR])
        player_rotate(*game);
    return (keycode);
}

void    init_window(t_game **g)
{
    ft_memset((*g)->keys, false, 283);
    (*g)->mlx = mlx_init();
    (*g)->win = mlx_new_window((*g)->mlx, WIDTH, HEIGHT, "cub3d");
    if (!(*g)->mlx)
    {
        fprintf(stderr, "Error: MLX initialization failed.\n");
        exit(EXIT_FAILURE);
    }
    (*g)->loop = loop;
    mlx_hook((*g)->win, 2, (1L << 0), keybrd_hook, g);
    mlx_hook((*g)->win, 3, (1L << 1), keyrelease_hook, g);
    mlx_hook((*g)->win, 17, (1L << 0), exit_x_button, *g);
    mlx_do_key_autorepeatoff((*g)->mlx);
    mlx_loop_hook((*g)->mlx, all_moves, g);
}