/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:52:34 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/07 18:35:38 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

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

void    fill(char **map, int x, int y, bool *error, bool ***visited, char player)
{
    if (*error == 1)
        return ;
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
            if (map->map[i - 1][j] == ' ' || map->map[i - 1][j] == '\0')
                _map[i][j + 1] = 'o';
            else
                _map[i][j + 1] = map->map[i - 1][j];
            j++;
        }
        while (j < map->max_width)
            _map[i][j++ + 1] = 'o';
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
void reverse_fill(char **map, int x, int y, t_map *map_info)
{
    if (x < 0 || x > (map_info->max_width + 1)
        || y < 0 || y >  (map_info->length + 1))
        return ;
    if (map[y][x] == 'v' || map[y][x] == '1'
        || map_info->parser.error == 1)
        return ;
    if (map[y][x] == '0')
    {
        printf("%d  %d\n", x, y);
        map_info->parser.error = 1;
        return ;
    }
    map[y][x] = 'v';

    reverse_fill(map, x + 1, y, map_info);
    reverse_fill(map, x - 1, y, map_info);
    reverse_fill(map, x, y + 1, map_info);
    reverse_fill(map, x, y - 1, map_info);
}

void flood_fill(t_map *map)
{
    char **buf_map = buffed_map(map);
    if (!buf_map)
    {
        ft_printf_fd(2, "Error\n buffer map allocation error\n");
        map->parser.error = 1;
        return ;
    }
    reverse_fill(buf_map, 0, 0, map);
    free_array(buf_map);
    if (map->parser.error == 1)
    {
        ft_printf_fd(2, "Error\nPlayer not surrounded by walls\n");
        return ;
    }
    initialize_visit_state(map);
    fill(map->map, map->x_player, map->y_player,
        &map->parser.error, &map->parser.visited, map->dir);
    if (map->parser.error == 1)
    {
        ft_printf_fd(2, "Error\nPlayer not surrounded by walls\n");
        return ;
    }
}
