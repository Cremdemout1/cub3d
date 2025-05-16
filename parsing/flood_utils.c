/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:44:21 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/16 13:44:42 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

bool	init_initial_state(t_variables *purse, int length)
{
	purse->visited = malloc(sizeof(int *) * length);
	if (!purse->visited)
		return (0);
	purse->y = 0;
	return (1);
}

// void	buffed_map_inner_loop(t_variables *p, t_map *map)
// {
// 	while (p->i <= map->length)
// 	{
// 		p->j = 0;
// 		p->_map[p->i] = malloc(sizeof (char) * (map->max_width + 2 + 1));
// 		p->_map[p->i][0] = 'o';
// 		while (p->j < map->width[p->i - 1])
// 		{
// 			if (map->map[p->i - 1][p->j] == ' '
// 					|| map->map[p->i - 1][p->j] == '\0')
// 				p->_map[p->i][p->j + 1] = 'o';
// 			else
// 				p->_map[p->i][p->j + 1] = map->map[p->i - 1][p->j];
// 			p->j++;
// 		}
// 		while (p->j < map->max_width)
// 			p->_map[p->i][p->j++ + 1] = 'o';
// 		p->_map[p->i][p->j] = 'o';
// 		p->_map[p->i][p->j + 1] = '\0';
// 		p->i++;
// 	}
// }
