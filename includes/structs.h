/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:53:22 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/30 03:58:19 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H
#define M_PI           3.14159265358979323846

typedef enum s_type
{
    WALL,
    FLOOR,
    PLAYER,
    VOID
}   t_type;

typedef enum s_direction
{
    NORTH = 0,
    SOUTH = 180,
    EAST = 90,
    WEST = 270
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
    int      *width; // x
    int      biggest_width;
    int      length; // y
    int      map_start;
    bool     player;
    int      x_player;
    int      y_player;
    char     **map;
    char     dir;
    int      facing;
    char     *N_text;
    char     *S_text;
    char     *E_text;
    char     *W_text;
    char     **texs;
    int      *floor_color; // to change to int *
    int      *ceiling_color; //to change to int *
    t_parse parser;
}   t_map;

// typedef struct s_player
// {
//     float dir;
//     int   x_pos;
//     int   y_pos;
// }   t_player;

typedef struct s_ray
{
    float angle;       // Ray angle in radians
    float distance;    // Distance to the wall hit
    float x_hit;       // x coordinate of the hit
    float y_hit;       // y coordinate of the hit
    int wall_hit;      // Type of wall hit (could be 0 for no hit, 1 for a wall)
} t_ray;

typedef struct s_ray_holder
{
    float   delta_x;
    float   delta_y;
    float   start_x;
    float   start_y;
    float   step_x;
    float   step_y;
    float   cur_x;
    float   cur_y;
    int     grid_x;
    int     grid_y;
    int     hor_step;
    int     ver_step;
}   t_ray_holder;


typedef struct s_game
{
    t_map    map;
    t_img    img;
    t_texture **texs;
    void	 *mlx;
    void	 *scdmlx;
	void	 *win;
	void	 *scdwin;
    void     *img_ptr;
    void     (*loop)(struct s_game *g);

}   t_game;

#endif