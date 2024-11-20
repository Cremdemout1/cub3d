/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:35 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/19 08:55:49 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void    get_length(t_map *map, char *filename)
{
    int fd;
    int y;
    char *line;

    fd = open(filename, O_RDONLY);
    y = 0;
    while (y < map->map_start)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        free(line);
        y++;
    }
    y = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        y++;
        free(line);
    }
    map->length = y;
    close(fd);
}

void    get_widths(t_map *map, char *filename)
{
    int y;
    int fd;
    int size;
    int *array;
    char *line;
    
    y = 0;
    size = 0;
    fd = open(filename, O_RDONLY);
    array = malloc (sizeof(int) * (map->length));
    if (!array)
        return ;
    while (y < map->map_start)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        free(line);
        y++;
    }
    y = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        array[y] = ft_strlen(line);
        if (array[y] > size)
            size = array[y];
        y++;
        free(line);
    }
    map->width = array;
    map->biggest_width = size;
    close(fd);
}

void    player_start_info(t_map *info, char dir, int x, int y)
{
    if (dir == 'N')
        info->facing = NORTH;
    else if (dir == 'S')
        info->facing = SOUTH;
    else if (dir == 'W')
        info->facing = WEST;
    else if (dir == 'E')
        info->facing = EAST;
    info->x_player = x;
    info->y_player = y;
    info->dir = dir;
}
