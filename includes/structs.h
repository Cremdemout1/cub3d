/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:53:22 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/18 05:33:59 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

typedef enum s_type
{
    WALL,
    FLOOR,
    PLAYER,
    VOID
}   t_type;

typedef enum s_direction
{
    NORTH,
    SOUTH,
    EAST,
    WEST
}   t_direction;

typedef struct s_parse
{
    int     numplayer;
    bool    error;
    bool    **visited;
}   t_parse;

typedef struct s_img
{
	void	*img;
    char    *img_addr;
    char	*img_pixel_ptr;
	int		bits_per_pixel;
	int	    endian;
	int		line_len;
}   t_img;

typedef struct s_texture {
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
} t_texture;

typedef struct s_map
{
    int     *width; // x
    int     biggest_width;
    int     length; // y
    int     map_start;
    bool    player;
    int     x_player;
    int     y_player;
    char    dir;
    char    **map;
    int     start_dir;
    char     *N_text;
    char     *S_text;
    char     *E_text;
    char     *W_text;
    char     **texs;
    int      *floor_color; // to change to int *
    int      *ceiling_color; //to change to int *
    t_parse parser;
}   t_map;

typedef struct s_game
{
    t_map    map;
    t_img    img;
    t_texture **texs;
    void	 *mlx;
	void	 *win;
    void     (*loop)(struct s_game *g);

}   t_game;

#endif