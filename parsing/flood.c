/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:52:34 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/16 18:53:33 by ycantin          ###   ########.fr       */
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
                || map->map[y][x] == 'S' || map->map[y][x] == 'W'
                    || map->map[y][x] == 'E')
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

// void flood_fill(t_map *map)
// {
//     initialize_visit_state(map);
//     Position *stack = malloc(sizeof(Position) * map->max_width * map->length);
//     if (!stack)
//     {
//         ft_printf_fd(2, "Error\nFailed to allocate memory for flood_fill stack\n");
//         map->parser.error = 1;
//         free(stack);
//         return ;
//     }
//     int stack_size = 0;
//     stack[stack_size++] = (Position){map->x_player, map->y_player};
//     while (stack_size > 0)
//     {
//         Position pos = stack[--stack_size];
//         int x = pos.x;
//         int y = pos.y;
//         if (y < 0 || y >= map->length || x < 0 || x >= map->width[y] || map->parser.visited[y][x])
//             continue ;
//         if (map->map[y][x] != '0' && map->map[y][x] != '1' && map->map[y][x] != map->dir)
//         {
//             ft_printf_fd(2, "Error\nPlayer not surrounded by walls\n");
//             map->parser.error = 1;
//             free(stack);
//             return ;
//         }
//         map->parser.visited[y][x] = true;
//         stack[stack_size++] = (Position){x + 1, y}; // right
//         stack[stack_size++] = (Position){x - 1, y}; // left
//         stack[stack_size++] = (Position){x, y + 1}; // down
//         stack[stack_size++] = (Position){x, y - 1}; // up
//     }
//     // for (int i = 0; i < map->length; i++)
//     // {
//     //     for (int j = 0; j < map->width[i]; j++)
//     //         printf("%d", map->parser.visited[i][j]);
//     //     printf("\n");
//     // }
//     free(stack);
// }

void    fill(char **map, int x, int y, bool *error, bool ***visited, char player)
{
    if (*error == 1)
        return ;
    // printf("x: %d   y: %d\n", x, y);
    if ((*visited)[y][x] == true)
        return ;
    if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != player)
    {
        *error = true;
        return ;
    }
    (*visited)[y][x] = true;
    fill(map, x + 1, y, error, visited, player);
    fill(map, x - 1, y, error, visited, player);
    fill(map, x, y + 1, error, visited, player);
    fill(map, x, y - 1, error, visited, player);
}

char **buffed_map(t_map *map)
{
    char **_map = malloc (sizeof (char *) * (map->length + 2 + 1));
    int i = 1;
    int j = 0;
    _map[0] = malloc(sizeof (char) * (map->max_width + 2 + 1));
    while(j < map->max_width + 1)
        _map[0][j++] = 'o';
    _map[0][j] = '\0';
    while (i <= map->length)
    {
        j = 0;
        _map[i] = malloc(sizeof (char) * (map->max_width + 2 + 1));
        _map[i][0] = 'o';
        while (j < map->width[i - 1])
        {
            if (map->map[i - 1][j] == ' ')
                _map[i][j + 1] = 'o';
            else
                _map[i][j + 1] = map->map[i - 1][j];
            j++;
        }
        while (j < map->max_width)
            _map[i][j++] = 'o';
        _map[i][j] = 'o';
        _map[i][j + 1] = '\0';
        i++;
    }
    j = 0;
    _map[i] = malloc(sizeof (char) * (map->max_width + 2 + 1));
    while(j < map->max_width + 1)
        _map[i][j++] = 'o';
    _map[i][map->max_width + 1] = '\0';
    _map[i + 1] = NULL;
    return(_map);
}
void reverse_flood(char **map, int x, int y, t_map *map_info)
{
    if (x < 0 || x > map_info->max_width || y < 0 || y >  map_info->length)
        return ;
    if (map[y][x] == 'v' || map[y][x] == '1' || map_info->parser.error == 1)
        return ;
    if (map[y][x] == '0')
    {
        printf("found leak\n");
        map_info->parser.error = 1;
        return ;
    }
    map[y][x] = 'v';

    reverse_flood(map, x + 1, y, map_info);
    reverse_flood(map, x - 1, y, map_info);
    reverse_flood(map, x, y + 1, map_info);
    reverse_flood(map, x, y - 1, map_info);
} //works everywhere but under for somw reason

void flood_fill(t_map *map)
{
    char **buf_map = buffed_map(map);
    if (!buf_map)
    {
        ft_printf_fd(2, "Error\n buffer map allocation error\n");
        map->parser.error = 1;
        return ;
    }
    for(int i = 0; buf_map[i]; i++)
        printf("%s\n", buf_map[i]);
    reverse_flood(buf_map, 0, 0, map);
    free_array(buf_map);
    if (map->parser.error == 1)
        return ;
    initialize_visit_state(map);
    // printf("%d\n", map->x_player);
    // printf("%d\n", map->y_player);
    printf("%d\n", map->parser.error);
    fill(map->map, map->x_player, map->y_player, &map->parser.error, &map->parser.visited, map->dir);
}