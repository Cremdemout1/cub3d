/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:52:34 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/06 18:30:11 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

typedef struct {
    int x;
    int y;
} Position;

// void flood_fill(t_map *map)
// {
//     if (map->map[map->y_player][map->x_player] == '1')
//         return;

//     Position *stack = malloc(sizeof(Position) * map->max_width * map->length);
//     if (!stack)
//     {
//         ft_printf_fd(2, "Error: Failed to allocate memory for flood_fill\n");
//         map->parser.error = 1;
//         return;
//     }

//     int stack_size = 0;
//     stack[stack_size++] = (Position){map->x_player, map->y_player};

//     while (stack_size > 0)
//     {
//         Position pos = stack[--stack_size];
//         int x = pos.x;
//         int y = pos.y;

//         // Out-of-bounds check
//         if (x < 0 || x >= map->max_width || y < 0 || y >= map->length)
//         {
//             free(stack);
//             ft_printf_fd(2, "Error: Out of bounds at (%d, %d)\n", x, y);
//             map->parser.error = 1;
//             return;
//         }

//         // Validate map character
//         char cell = map->map[y][x];
//         if (cell != '0' && cell != '1' && cell != 'V' && cell != map->dir)
//         {
//             free(stack);
//             ft_printf_fd(2, "Error: Invalid character '%c' at (%d, %d)\n", cell, x, y);
//             map->parser.error = 1;
//             return;
//         }
//         if (cell == '0')
//         {
//             map->map[y][x] = 'V';
//             stack[stack_size++] = (Position){x + 1, y}; // right
//             stack[stack_size++] = (Position){x - 1, y}; // left
//             stack[stack_size++] = (Position){x, y + 1}; // down
//             stack[stack_size++] = (Position){x, y - 1}; // up
//         }
//     }
//     for (int i = 0; i < map->length; i++)
//     {
//         for(int j = 0; j < map->width[i]; j++)
//             printf("%c", map->map[i][j]);
//         printf("\n");
//     }
//     free(stack);
// }

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
        visited[y] = malloc (sizeof(bool) * map->width[y]);
        if (!visited[y])
            return ;
        x = 0;
        while (x < map->width[y])
        {
            if (map->map[y][x] == '0' || map->map[y][x] == 'N'
                || map->map[y][x] == 'S' || map->map[y][x] == 'W' || map->map[y][x] == 'E')
                    visited[y][x] = false;
            else if(map->map[y][x] == '1')
                visited[y][x] = true;
            else
                visited[y][x] = false;
            x++;
        }
        y++;
    }
    map->parser.visited = visited;
}

void flood_fill(t_map *map)
{
    initialize_visit_state(map);
    Position *stack = malloc(sizeof(Position) * map->max_width * map->length);
    if (!stack)
    {
        ft_printf_fd(2, "Error: Failed to allocate memory for flood_fill stack\n");
        map->parser.error = 1;
        free(stack);
        return ;
    }
    int stack_size = 0;
    stack[stack_size++] = (Position){map->x_player, map->y_player};
    while (stack_size > 0)
    {
        Position pos = stack[--stack_size];
        int x = pos.x;
        int y = pos.y;
        if (y < 0 || y >= map->length || x < 0 || x >= map->width[y] || map->parser.visited[y][x])
            continue ;
        if (map->map[y][x] != '0' && map->map[y][x] != '1' && map->map[y][x] != map->dir)
        {
            ft_printf_fd(2, "Error: Player not surrounded by walls\n");
            map->parser.error = 1;
            free(stack);
            return ;
        }
        map->parser.visited[y][x] = true;
        stack[stack_size++] = (Position){x + 1, y}; // right
        stack[stack_size++] = (Position){x - 1, y}; // left
        stack[stack_size++] = (Position){x, y + 1}; // down
        stack[stack_size++] = (Position){x, y - 1}; // up
    }
    // for (int i = 0; i < map->length; i++)
    // {
    //     for (int j = 0; j < map->width[i]; j++)
    //         printf("%d", map->parser.visited[i][j]);
    //     printf("\n");
    // }
    free(stack);
}

