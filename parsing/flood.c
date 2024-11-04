/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:52:34 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/04 04:56:46 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

// bool fill(t_map *map, int x, int y)
// {
//     if (map->parser.error)
//         return map->parser.error;
//     if (map->map[y][x + 1] == ' ' || map->map[y][x - 1] == ' '
//         || map->map[y + 1][x] == ' ' || map->map[y - 1][x] == ' ')
//             return (ft_printf_fd(2, "iteration went out of bounds\n"),
//                 map->parser.error = true, map->parser.error);
//     if (map->parser.visited[y][x])
//         return (map->parser.error = true, map->parser.error);
//     map->parser.visited[y][x] = true;
//     map->map[y][x] = 'V';
//     if (!map->parser.visited[y][x + 1])
//         if (fill(map, x + 1, y))
//             return (map->parser.error);
//     if (!map->parser.visited[y][x - 1])
//         if (fill(map, x - 1, y))
//             return (map->parser.error);
//     if (!map->parser.visited[y + 1][x])
//         if (fill(map, x, y + 1))
//             return (map->parser.error);
//     if (!map->parser.visited[y - 1][x])
//         if (fill(map, x, y - 1))
//             return (map->parser.error);
//     return (map->parser.error);
// }

// bool    flood_fill(t_map *map)
// {
//     map->parser.error = false;
//     if (fill(map, map->x_player, map->y_player) == true) //error found
//         return (false);
//     return (true);
// }

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Position;

// void flood_fill(t_map *map)
// {
//     if (map->map[map->y_player][map->x_player] == '1')
//         return;
        
//     Position *stack = malloc(sizeof(Position) * map->biggest_width * map->length); // Stack for positions
//     int stack_size = 0;

//     // Push the starting position
//     stack[stack_size++] = (Position){map->y_player, map->x_player};

//     while (stack_size > 0) {
//         // Pop the last position
//         Position pos = stack[--stack_size];
//         int x = pos.x;
//         int y = pos.y;

//         // Check bounds
//         if (x < 0 || x >= map->width[y] || y < 0 || y >= map->length)
//         {
//             continue ; // Out of bounds
//         if (map->map[y][x] != '0')
//             continue ;
            
//         map->map[y][x] = 'V';
//         stack[stack_size++] = (Position){x + 1, y}; // right
//         stack[stack_size++] = (Position){x - 1, y}; // left
//         stack[stack_size++] = (Position){x, y + 1}; // down
//         stack[stack_size++] = (Position){x, y - 1}; // up
//     }

//     free(stack);
// }

void flood_fill(t_map *map)
{
    if (map->map[map->y_player][map->x_player] == '1')
        return;
    Position *stack = malloc(sizeof(Position) * map->biggest_width * map->length);
    int stack_size = 0;
    stack[stack_size++] = (Position){map->y_player, map->x_player};
    while (stack_size > 0)
    {
        Position pos = stack[--stack_size];
        int x = pos.x;
        int y = pos.y;
        if (x < 0 || x >= map->biggest_width || y < 0 || y >= map->length) {
            free(stack);
            ft_printf_fd(2, "Error: Reached out of bounds at (%d, %d)\n", x, y);
            map->parser.error = 1;
            return;
        }
        if (map->map[y][x] != '0' && map->map[y][x] != '1' && map->map[y][x] != 'V' && map->map[y][x] != map->dir) {
            free(stack);
            ft_printf_fd(2, "Error: Invalid character '%c' at (%d, %d)\n", map->map[y][x], x, y);
            map->parser.error = 1;
            return;
        }
        if (map->map[y][x] == '0')
        {
            map->map[y][x] = 'V';

            stack[stack_size++] = (Position){x + 1, y}; // right
            stack[stack_size++] = (Position){x - 1, y}; // left
            stack[stack_size++] = (Position){x, y + 1}; // down
            stack[stack_size++] = (Position){x, y - 1}; // up
        }
    }

    free(stack);
}


void    initialize_visit_state(t_map *map)
{
    int x;
    int y;
    bool **visited;
    
    visited = malloc(sizeof(int *) * map->length);
    if (!visited)
        return ;
    y = 0;
    while (y < map->length)
    {
        visited[y] = malloc (sizeof(int) * map->width[y]);
        if (!visited[y])
            return ;
        x = 0;
        while (x < map->width[y])
        {
            if (map->map[y][x] == '0' || map->map[y][x] == 'N'
                || map->map[y][x] == 'S' || map->map[y][x] == 'W' || map->map[y][x] == 'E')
                    visited[y][x] = 0;
            else if(map->map[y][x] == '1')
                visited[y][x] = 1;
            else
                visited[y][x] = -1;
            x++;
        }
        y++;
    }
    map->parser.visited = visited;
}
