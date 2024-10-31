/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:35 by ycantin           #+#    #+#             */
/*   Updated: 2024/10/30 23:32:58 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

bool    valid_arguments(int argc, char **argv)
{
    int i;

    i = 0;
    if (argc != 2 || !argv[1] || !argv[1][0])
        return (false);
    while (argv[1][i] && argv[1][i] != '.')
        i++;
    if (ft_strcmp(argv[1] + i, ".cub") != 0) //works?? huh
        return (false);
    return (true);
}

// char    *get_map(int fd, t_map *map)
// {
//     int i;
//     char *line;
//     char *buf;
//     char *temp;
//     i = 0;
//     buf = NULL;
//     while (1)
//     {
//         line = get_next_line(fd);
//         if (!line)
//             break ;
//         i++;
//         if (buf)
//         {
//             temp = ft_strjoin(buf, line);
//             free(buf);
//             buf = ft_strdup(temp);
//             free(temp);
//         }
//         else
//             buf = ft_strdup(line);
//         free(line);
//     }
//     return (map->length = i, buf);
// }

char    **get_map(int fd, t_map *map)
{
    int i = 0;
    int line_count = 0;
    int line_len;
    char *line;
    char **buf;

    line_len = 0;
    while ((line = get_next_line(fd)))
    {
        line_len = ft_strlen(line) + 2;
        if (line_len > i)
            i = line_len;
        line_count++;
        free(line);
    }
    map->length = line_count;
    map->biggest_width = i;
    close(fd);
    fd = open("map.cub", O_RDONLY);
    i = 0;
    line_len = 0;
    buf = (char **)malloc(sizeof(char *) * (line_count + 2 + 1));
    if (!buf)
        return NULL;
    buf[i] = (char *)malloc(sizeof(char) * (map->biggest_width + 1));
    if (!buf[i])
        return NULL;
    ft_memset(buf[i], ' ', map->biggest_width);
    buf[i][map->biggest_width] = '\0';
    i++;
    while ((line = get_next_line(fd)))
    {
        line_len = ft_strlen(line);

        if (line[line_len - 1] == '\n')
            line_len--;
        buf[i] = (char *)malloc(sizeof(char) * (line_len + 2 + 1)); // 2 extra for spaces
        if (!buf[i])
            return NULL;
        buf[i][0] = ' ';
        ft_strcpy(buf[i] + 1, line);
        buf[i][line_len + 1] = ' ';
        buf[i][line_len + 2] = '\0';
        free(line);
        i++;
    }
    buf[i] = (char *)malloc(sizeof(char) * (map->biggest_width + 1));
    if (!buf[i])
        return NULL;
    ft_memset(buf[i], ' ', map->biggest_width);
    buf[i][map->biggest_width] = '\0';
    buf[i + 1] = NULL;
    map->length = i + 1;
    return (buf);
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

void    get_widths(t_map *map)
{
    int y;
    int *array;
    int biggest;
    
    y = 0;
    biggest = 0;
    array = malloc (sizeof(int) * map->length);
    if (!array)
        return ;
    while (y < map->length)
    {
        array[y] = ft_strlen(map->map[y]);
        if (array[y] > biggest)
            biggest = array[y];
        y++;
    }
    map->width = array;
    map->biggest_width = biggest;
}

bool found_player(t_map *info)
{
    int x;
    int y;
    
    y = 0;
    while (info->map[y])
    {
        x = 0;
        while (info->map[y][x])
        {
            if (info->map[y][x] == 'N')
                return(player_start_info(info, 'N', x, y), 1);
            else if (info->map[y][x] == 'S')
                return(player_start_info(info, 'S', x, y), 1);
            else if (info->map[y][x] == 'E')
                return(player_start_info(info, 'E', x, y), 1);
            else if (info->map[y][x++] == 'W')
                return(player_start_info(info, 'W', x, y), 1);
        }
        y++;
    }
    return (ft_printf_fd(2, "no player found: "), false);
}

bool     fill(t_map *map, int x, int y)
{
    if (map->parser.error)
        return map->parser.error;
    if (x < 0 || y < 0 || y >= map->length || x >= map->width[y]
        || !map->map[y][x] || map->map[y][x] == ' ')
            return (ft_printf_fd(2, "iteration went out of bounds\n")
            , map->parser.error = true, map->parser.error);
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
    if (fill(map, map->x_player, map->y_player))
        return (false);
    for(int i = 0; map->map[i] != NULL; i++)
        printf("%s\n", map->map[i]);
    return (true);
}

void    initialize_visit_state(t_map *map)
{
    int x;
    int y;
    int i;
    bool **visited;
    visited = malloc(sizeof(bool *) * map->length);
    if (!visited)
        return ; //if no visited map initialized, all breaks
    y = 0;
    while (y < map->length)
    {
        printf("width:  %d\n", map->width[y]);
        visited[y] = malloc (sizeof(bool) * map->width[y]);
        if (!visited[y])
        {
            i = 0;
            while (i < y)
                free(visited[i++]);
            free(visited);
            return ;
        }
        x = 0;
        while (x < map->width[y])
        {
            if (map->map[y][x] == '0' || map->map[y][x] == 'N' || map->map[y][x] == ' '
                || map->map[y][x] == 'S' || map->map[y][x] == 'W' || map->map[y][x] == 'E')
                    visited[y][x] = false;
            else
                visited[y][x] = true;
            x++;
        }
        y++;
    }
    map->parser.visited = visited;
}

void    new_widths(t_map *map)
{
    int y;
    int *array;    
    
    y = 1;
    array = malloc (sizeof(int) *( map->length));
    if (!array)
        return ;
    array[0] = map->biggest_width;
    while (y < map->length)
    {
        array[y] = map->width[y - 1] + 2;
        y++;
    }
    array[y - 1] = map->biggest_width;
    free(map->width);
    map->width = array;
}

void bufferize_map(char **old_map, t_map *info)
{
    char **new_map;
    int size = 0;

    while (old_map[size])
        size++;
    new_map = malloc(sizeof(char *) * (size + 3));
    if (!new_map)
        return ;
    new_map[0] = malloc(sizeof(char) * (info->biggest_width + 2));
    ft_memset(new_map[0], ' ', (info->biggest_width + 2));
    new_map[0][(info->biggest_width + 2)] = '\0';
    size = 0;
    printf("new string:%s\n", new_map[0]);
    while (old_map[size])
    {
        char temp[info->width[size] + 2];
        temp[0] = ' ';
        ft_strcpy(temp + 1, old_map[size]);
        temp[info->width[size] + 1] = ' ';
        temp[info->width[size] + 2] = '\0';
        new_map[size + 1] = ft_strdup(temp);
        printf("new string:%s\n", new_map[size + 1]);
        size++;
    }
    new_map[size + 1] = malloc(sizeof(char) * (info->biggest_width + 2));
    ft_memset(new_map[size + 1], ' ', (info->biggest_width + 2));
    new_map[size + 1][(info->biggest_width + 2)] = '\0';
    new_map[size + 2] = NULL;
    printf("new string:%s\n", new_map[size + 1]);
    free_array(info->map);
    info->map = new_map;
    info->length += 2;
    new_widths(info);
}

bool    init_map_and_player(t_map *map_info, int fd)
{
    char **map;
    // char *buf;

    // buf = get_map(fd, map_info);
    // close(fd);
    // if (!buf)
    //     return (ft_printf_fd(2, "buffer error\n"), false);
    // map = ft_split(buf, '\n');

    // for(int i = 0; map[i] != NULL; i++)
        // printf("%s\n", map[i]);
    // free(buf);
    // if (!map)
        // return (ft_printf_fd(2, "map error\n"), false);
    map = get_map(fd, map_info);
    map_info->map = map;
    for(int i = 0; map[i] != NULL; i++)
        printf("%s\n", map[i]);
    //map_info->map = get_map(fd, map_info);
    if (!found_player(map_info))
    {
        // free_array(map);
        return (ft_printf_fd(2, "initiation error\n"), false);
    }
    get_widths(map_info);
    //bufferize_map(map_info->map, map_info);
    initialize_visit_state(map_info);
    const char *direction_names[] = { "NORTH", "SOUTH", "EAST", "WEST" };
    printf("player initial direction: %s\n", direction_names[map_info->start_dir]);
    printf ("player x: %d, player y: %d\n", map_info->x_player, map_info->y_player);
    return (true);
}
