/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:49 by ycantin           #+#    #+#             */
/*   Updated: 2024/10/29 19:55:59 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H
#include "main.h"
#include "structs.h"

bool    valid_arguments(int argc, char **argv);
bool    flood_fill(t_map *map, int fd);
char    *get_map(int fd, t_map *map);

#endif
