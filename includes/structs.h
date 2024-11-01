/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:53:22 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/01 13:59:55 by ycantin          ###   ########.fr       */
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

typedef struct s_window
{
	void	*mlx;
	void	*win;
	void	*img;
    char	*img_pixel_ptr;
	int		bits_per_pixel;
	int	    endian;
	int		line_len;
}   t_window;

typedef struct s_map
{
    int     *width; // x
    int     biggest_width;
    int     length; // y
    bool    player;
    int     x_player;
    int     y_player;
    char    **map;
    int     start_dir;
    t_parse parser;
}   t_map;

typedef struct s_game
{
    t_map    map;
    t_window window;
    void     (*loop)(struct s_game *g);

}   t_game;

#endif