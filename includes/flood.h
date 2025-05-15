/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:35:10 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/15 15:46:40 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOOD_H
#define FLOOD_H

#include "main.h"
#include "structs.h"

void    flood_fill(t_map *map);
void    initialize_visit_state(t_map *map);

bool	init_initial_state(t_variables *purse, int length);
void	buffed_map_inner_loop(t_variables *p, t_map *map);

#endif