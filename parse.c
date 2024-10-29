/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:35 by ycantin           #+#    #+#             */
/*   Updated: 2024/10/29 19:58:31 by ycantin          ###   ########.fr       */
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

// void    get_map(int fd)
// {
//     //char **map;
//     int i;
//     char *line;
//     char *buf;
//     char *temp;
//     i = 0;
//     buf = NULL;
//     temp = NULL;
//     while (1)
//     {
//         line = get_next_line(fd);
//         if (!line)
//             break ;
//         i++;
//         if (buf)
//         {
//             temp = ft_strjoin(buf, ":");
             // free(buf);
//             buf = ft_strjoin(temp, line);
//             free(temp);
//         }
//         else
//             buf = ft_strdup(line);
//         free(line);
//     }
//     printf("%s", buf);
//     free(buf);
// }

char    *get_map(int fd, t_map *map)
{
    int i;
    char *line;
    char *buf;
    char *temp;
    i = 0;
    buf = NULL;
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        i++;
        if (buf)
        {
            temp = ft_strjoin(buf, line);
            free(buf);
            buf = ft_strdup(temp);
            free(temp);
        }
        else
            buf = ft_strdup(line);
        free(line);
    }
    return (map->length = i, buf);
}

bool    flood_fill(t_map *map_info, int fd)
{
    char **map;
    char *buf;

    buf = get_map(fd, map_info);
    map = ft_split(buf, '\n');
    free(buf);
    // fill();
    free_array(map);
    return (false);
}