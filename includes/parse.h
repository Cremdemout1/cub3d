/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:53:04 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/20 18:53:17 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "main.h"
# include "structs.h"

bool	valid_arguments(int argc, char **argv);
char	**get_map(t_map *map, char *filename);
int		get_starting_info(t_map *map, char *filename);
bool	init_map_and_player(t_map *map_info, char *filename);

char	**get_map(t_map *map, char *filename);

void	get_length(t_map *map, char *filename);
void	get_widths(t_map *map, char *filename);
void	player_start_info(t_map *info, char dir, int x, int y);

void	free_starting_info(t_map *map);
void	free_str_textures(t_map *map);
bool	valid_map_char(char c);
bool	valid_arguments(int argc, char **argv);
bool	return_value(t_variables *purse);

int		all_found(int *found);
bool	has_non_num_val(char *str);
bool	is_valid_file(char *file);
int		is_empty(char *str);
int		handle_colors_and_textures(t_variables *p, int *found, t_map *map);
int		prep_line(t_variables *p);
void	read_until_eof(t_variables *p, t_map *map);
int		prep_file(t_variables *p, t_map *map, char *filename);
int		parse_info(t_variables *p, t_map *map);
void	handle_texture(t_map *map, char *texture, int *found, int dir);
int		handle_color(t_map *map, char *color, int *found, int type);

void	format_line(t_variables *p, int max_width);
void	skip_initial_lines(t_map *map, int fd);

#endif
