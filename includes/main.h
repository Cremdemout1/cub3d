/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:44:33 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/20 03:48:57 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
#define CUBED_H

#define HEIGHT       800
#define WIDTH        800
#define XPM_X        16
#define XPM_Y        16
#define FOV          60
#define PLAYER_SPEED 4
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

void    free_resources(t_map *map);
int     exit_t(t_game *g);
int     destroy(t_game *window);

void    draw_map(t_game *game);

void    cast_all_rays(t_game *game);


#endif