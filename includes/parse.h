/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:38:06 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 15:38:26 by ycantin          ###   ########.fr       */
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

char	*add_bigger_buf(int decider, t_map *map, int i, char *line);
char	*create_biggest_buf(t_map *map);
char	**get_map(t_map *map, char *filename);

void	get_length(t_map *map, char *filename);
void	get_widths(t_map *map, char *filename);
void	player_start_info(t_map *info, char dir, int x, int y);

void	free_starting_info(t_map *map);
void	free_str_textures(t_map *map);
bool	valid_map_char(char c);
bool	valid_arguments(int argc, char **argv);
bool	return_value(t_variables *purse);

#endif
