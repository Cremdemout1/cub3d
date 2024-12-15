/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:44:33 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/15 14:25:59 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
#define CUBED_H

#define HEIGHT       800
#define WIDTH        1000
#define VISITED      2
#define XPM_X        64
#define XPM_Y        64
#define FOV          60
#define PLAYER_SPEED  3
#define ROT_SPEED     1.8
#define PLAYER_RADIUS 0.2
#define M_PI           3.14159265358979323846
#define LEFT_ARR     281
#define RIGHT_ARR    282

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>
#include "flood.h"
#include "parse.h"
#include "raycaster.h"
#include "structs.h" 
#include "my_mlx.h"
#include "libft/libft.h"
#include "../minilibx-linux/mlx.h"

void    free_resources(t_game **game);
int     exit_t(t_game *g);

void    draw_map(t_game *game);

void    cast_all_rays(t_game *game);
int     keybrd_hook(int key, t_game **game);

float   deg_to_rad(int degree);

unsigned int    rgb_to_color(int *rgb);
int             tex_color(int tex_X, int tex_Y, t_texture *t);

void    player_move(t_game *game);
void    player_strafe(t_game *game);
void    player_rotate(t_game *game);

#endif