/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:23:56 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 18:13:33 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# define M_PI	3.14159265358979323846
# include <stdbool.h>

typedef enum s_type
{
	WALL,
	FLOOR,
	PLAYER,
	VOID
}	t_type;

typedef enum s_direction
{
	NORTH = 270,
	SOUTH = 90,
	EAST = 0,
	WEST = 180
}	t_direction;

typedef struct s_parse
{
	int		numplayer;
	bool	error;
	bool	**visited;
}	t_parse;

typedef struct s_img
{
	void	*img;
	char	*img_addr;
	char	*img_pixel_ptr;
	int		bits_per_pixel;
	int		endian;
	int		line_len;
}	t_img;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_map
{
	int		*width; // x
	int		max_width;
	int		length; // y
	int		map_start;
	bool	player;
	int		x_player;
	int		y_player;
	char	**map;
	char	dir;
	int		facing;
	char	**texs;
	int		*floor_color;
	int		*ceiling_color;
	t_parse	parser;
}	t_map;

typedef struct s_player_info
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;	
}	t_player_info;

typedef struct s_wall
{
	int			line_height;
	int			top;
	int			bottom;
	double		wall_x;
	t_texture	*texture;
	int			texture_x;
	double		t_step;
	double		texture_pos;
}	t_wall;

typedef struct s_raycast
{
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	step_x;
	double	step_y;
	double	perp_wall_dist;
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
}	t_raycast;

typedef struct s_game
{
	t_map			map;
	t_img			img;
	t_texture		**texs;
	t_player_info	player;
	t_wall			wall;
	t_raycast		ray;
	void			*mlx;
	void			*win;
	void			*img_ptr;
	void			(*loop)(struct s_game *g);
	bool			keys[283];
	struct timeval	last_time;
	double			dt;
}	t_game;

typedef struct s_fill_context
{
	char		**map;
	bool		**visited;
	bool		*error;
	char		player;
}	t_fill_context;

typedef struct s_var_holder
{
	int		i;
	int		j;
	int		y;
	int		fd;
	int		len;
	int		size;
	int		*array;
	char	*line;
	int		x;
	int		count;
	int		error;
	int		is_empty;
	char	**_map;
	char	**buf;
	bool	**visited;
	int		pr_min_x;
	int		pr_min_y;
	int		pr_plus_x;
	int		pr_plus_y;
}	t_variables;

#endif