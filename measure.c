/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:35 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/01 13:08:28 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

void    get_length(t_map *map, char *filename)
{
    int fd;
    int y;
    int size;
    char *line;
    int len;

    fd = open(filename, O_RDONLY);
    y = 0;
    size = 0;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        len = ft_strlen(line);
        if (len > size)
            size = len;
        y++;
        free(line);
    }
    map->length = y + 2;
    map->biggest_width = size + 1;
    close(fd);
}

void    get_widths(t_map *map, char *filename)
{
    int y;
    int fd;
    int *array;
    char *line;
    
    y = 1;
    fd = open(filename, O_RDONLY);
    array = malloc (sizeof(int) * (map->length));
    if (!array)
        return ;
    array[0] = map->biggest_width;
    while (y < map->length - 1)
    {
        line = get_next_line(fd);
        array[y] = ft_strlen(line);
        y++;
        free(line);
    }
    array[y] = map->biggest_width;
    map->width = array;
    close(fd);
}

void    player_start_info(t_map *info, char dir, int x, int y)
{
    if (dir == 'N')
        info->start_dir = NORTH;
    else if (dir == 'S')
        info->start_dir = SOUTH;
    else if (dir == 'W')
        info->start_dir = WEST;
    else if (dir == 'E')
        info->start_dir = EAST;
    info->x_player = x;
    info->y_player = y;
}
