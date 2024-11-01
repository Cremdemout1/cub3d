/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:49 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/01 07:40:46 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H
#include "main.h"
#include "structs.h"

bool    valid_arguments(int argc, char **argv);
bool    flood_fill(t_map *map);
char    **get_map(t_map *map, char *filename);
bool    init_map_and_player(t_map *map_info, char *filename);


#endif
