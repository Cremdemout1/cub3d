/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:49 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/03 17:34:16 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H
#include "main.h"
#include "structs.h"

bool    valid_arguments(int argc, char **argv);
char    **get_map(t_map *map, char *filename);
int get_starting_info(t_map *map, char *filename) ;
bool    init_map_and_player(t_map *map_info, char *filename);

char    *add_bigger_buf(int decider, t_map *map, int i, char *line);
char    *create_biggest_buf(t_map *map);
char    **get_map(t_map *map, char *filename);

void    get_length(t_map *map, char *filename);
void    get_widths(t_map *map, char *filename);
void    player_start_info(t_map *info, char dir, int x, int y);


#endif
