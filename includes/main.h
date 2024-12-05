/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:44:33 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/05 21:05:23 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
#define CUBED_H

#define HEIGHT       800
#define WIDTH        1000
#define VISITED      2
#define XPM_X        16
#define XPM_Y        16
#define FOV          60
#define PLAYER_SPEED 1
#define ROT_SPEED    0.45
#define M_PI           3.14159265358979323846

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <math.h>
#include "flood.h"
#include "parse.h"
#include "structs.h" 
#include "my_mlx.h"
#include "libft/libft.h"
#include "../minilibx-linux/mlx.h"

void    free_resources(t_game **game);
int     exit_t(t_game *g);
int     destroy(t_game *window);

void    draw_map(t_game *game);

void    cast_all_rays(t_game *game);
int     keybrd_hook(int key, t_game **game);

float   deg_to_rad(int degree);
void    color_background(t_game *game);
void	init_default_bg(t_game *game);

#endif