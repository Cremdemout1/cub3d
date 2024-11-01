/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:52:34 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/01 13:08:57 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

bool fill(t_map *map, int x, int y)
{
    if (map->parser.error)
        return map->parser.error;
    if (map->map[y][x + 1] == ' ' || map->map[y][x - 1] == ' '
        || map->map[y + 1][x] == ' ' || map->map[y - 1][x] == ' ')
            return (ft_printf_fd(2, "iteration went out of bounds\n"),
                map->parser.error = true, map->parser.error);
    if (map->parser.visited[y][x])
        return (map->parser.error = true, map->parser.error);
    map->parser.visited[y][x] = true;
    map->map[y][x] = 'V';
    if (!map->parser.visited[y][x + 1])
        if (fill(map, x + 1, y))
            return (map->parser.error);
    if (!map->parser.visited[y][x - 1])
        if (fill(map, x - 1, y))
            return (map->parser.error);
    if (!map->parser.visited[y + 1][x])
        if (fill(map, x, y + 1))
            return (map->parser.error);
    if (!map->parser.visited[y - 1][x])
        if (fill(map, x, y - 1))
            return (map->parser.error);
    return (map->parser.error);
}

bool    flood_fill(t_map *map)
{
    map->parser.error = false;
    if (fill(map, map->x_player, map->y_player) == true) //error found
        return (false);
    return (true);
}

void    initialize_visit_state(t_map *map)
{
    int x;
    int y;
    bool **visited;
    
    visited = malloc(sizeof(bool *) * map->length);
    if (!visited)
        return ;
    y = 0;
    while (y < map->length)
    {
        visited[y] = malloc (sizeof(bool) * map->width[y]);
        if (!visited[y])
            return ;
        x = 0;
        while (x < map->width[y])
        {
            if (map->map[y][x] == '0' || map->map[y][x] == 'N' || map->map[y][x] == ' '
                || map->map[y][x] == 'S' || map->map[y][x] == 'W' || map->map[y][x] == 'E')
                    visited[y][x] = false;
            else if(map->map[y][x] == '1')
                visited[y][x] = true;
            x++;
        }
        y++;
    }
    map->parser.visited = visited;
}
