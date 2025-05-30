/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:38:39 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 15:38:52 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
# define MY_MLX_H

void	image_put_pixel(t_img *img, int x, int y, int color);
void	loop(t_game *g);
void	update_dt(t_game *game);

void	img_placeholder(t_game **game);
int		keybrd_hook(int key, t_game **game);
int		keyrelease_hook(int key, t_game **game);
int		all_moves(t_game **game, int keycode);
void	init_window(t_game **g);

void	load_textures(t_game **game);
void	load_player_texture(t_game **game);

#endif