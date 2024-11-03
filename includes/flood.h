/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:35:10 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/03 15:36:18 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOOD_H
#define FLOOD_H

#include "main.h"
#include "structs.h"

void    flood_fill(t_map *map);
bool    fill(t_map *map, int x, int y);
void    initialize_visit_state(t_map *map);

#endif