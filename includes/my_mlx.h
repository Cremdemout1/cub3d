/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:35:10 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/03 09:09:22 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
#define MY_MLX_H

# define XK_ESCAPE 0xff1b
# define XK_A 0x0061
# define XK_B 0x0062
# define XK_C 0x0063
# define XK_D 0x0064
# define XK_E 0x0065
# define XK_F 0x0066
# define XK_G 0x0067
# define XK_H 0x0068
# define XK_I 0x0069
# define XK_J 0x006a
# define XK_K 0x006b
# define XK_L 0x006c
# define XK_M 0x006d
# define XK_N 0x006e
# define XK_O 0x006f
# define XK_P 0x0070
# define XK_Q 0x0071
# define XK_R 0x0072
# define XK_S 0x0073
# define XK_T 0x0074
# define XK_U 0x0075
# define XK_V 0x0076
# define XK_W 0x0077
# define XK_X 0x0078
# define XK_Y 0x0079
# define XK_Z 0x007a
# define XK_RETURN 0xFF0D
# define XK_KP_LEFT 0xff96
# define XK_KP_UP 0xff97
# define XK_KP_RIGHT 0xff98
# define XK_KP_DOWN 0xff99
# define XK_KP_SPACE 0xff80
# define XK_KP_TAB 0xff89
# define XK_BRACKETLEFT 0x005b
# define XK_BRACKETRIGHT 0x005d
# define M_PI 3.14159265358979323846

// int x_button(t_window *window);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);


#endif