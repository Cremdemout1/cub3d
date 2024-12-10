/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:53:22 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/10 19:31:27 by ycantin          ###   ########.fr       */
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
    NORTH = 270,
    SOUTH = 90,
    EAST = 0,
    WEST = 180
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
    int      max_width;
    int      length; // y
    int      map_start;
    bool     player;
    double      x_player;
    double      y_player;
    char     **map;
    char     dir;
    int      facing;
    char     **texs;
    int      *floor_color; // to change to int *
    int      *ceiling_color; //to change to int *
    t_parse parser;
}   t_map;

typedef struct s_player_info
{
    double posX;
    double posY;
    double dirX;
    double dirY;
    double planeX;
    double planeY;    
}   t_player_info;

typedef struct s_wall
{
    int         lineHeight;
    int         top;
    int         bottom;
    double      wallX;
    t_texture   *texture;
    int         textureX;
    double      t_step;
    double      texture_pos;
}   t_wall;

typedef struct s_raycast 
{
    double cameraX;
    double rayDirX;
    double rayDirY;    
    double sideDistX;
    double sideDistY;    
    double deltaDistX;
    double deltaDistY;    
    double stepX;
    double stepY;
    double perpWallDist;
    int    hit;    
    int    side;
    int    mapX;
    int    mapY;
}   t_raycast;

typedef struct s_game
{
    t_map           map;
    t_img           img;
    t_texture       **texs;
    t_player_info   player;
    t_wall          wall;
    t_raycast       ray;
    void	        *mlx;
	void	        *win;
    void            *img_ptr;
    void            (*loop)(struct s_game *g);

}   t_game;

#endif