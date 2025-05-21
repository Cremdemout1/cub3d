/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:40:46 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/21 13:45:07 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define HEIGHT			1000
# define WIDTH			1200
# define VISITED		2
# define XPM_X			64
# define XPM_Y			64
# define FOV			0.66
# define PLAYER_SPEED	3
# define ROT_SPEED		1.8
# define PLAYER_RADIUS	0.1
# define M_PI			3.14159265358979323846
# define LEFT_ARR		281
# define RIGHT_ARR		282

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <sys/time.h>
# include "flood.h"
# include "parse.h"
# include "raycaster.h"
# include "structs.h" 
# include "my_mlx.h"
# include "libft/libft.h"
# include "../minilibx-linux/mlx.h"

void			free_resources(t_game **game);
void			game_error(t_game **g);
int				exit_x_button(void *param);
void			free_textures(t_texture **textures, int count, void *mlx);

void			cast_all_rays(t_game *game);
int				keybrd_hook(int key, t_game **game);

float			deg_to_rad(int degree);

unsigned int	rgb_to_color(int *rgb);
int				tex_color(int tex_X, int tex_Y, t_texture *t);

void			player_move(t_game *game);
void			player_rotate(t_game *game);
void			prep_rotation(t_game *game, double rot_speed);
void			assign_potential_coords(t_variables *p, double x, double y);
void			move_player_by_direction(t_game *game, double dx,
					double dy, double speed_multiplier);
void			change_player_coords(t_game *game, double nextX, double nextY);

#endif