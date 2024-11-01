/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:35 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/01 13:08:49 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

char    *add_bigger_buf(int decider, t_map *map, int i, char *line)
{
    int len;
    int size;
    char *str;
    
    size = ft_strlen(line);
    if (decider == -1)
        len = map->width[i - 1];
    else if (decider == 1)
        len = map->width[i + 1];
    str = malloc(sizeof(char) * (len + 2));
    if (!str)
        return (NULL);
    str[0] = ' ';
    ft_strcpy(str + 1, line);
    
    if (line[size - 1] !='\n')
    {
        while (size < (len - 1))
            str[size++] = ' ';
        str[size + 1] = ' ';
        str[size + 2] = '\0';
    }
    else
    {    
        while ((size) < len)
            str[size++] = ' ';
        str[size] = ' ';
        str[size + 1] = '\0';
    }
    return (str);
}


char *create_biggest_buf(t_map *map)
{
    char *str;
    
    str = (char *)malloc(sizeof(char) * (map->biggest_width + 1));
    if (!str)
        return (NULL);
    ft_memset(str, ' ', map->biggest_width);
    str[map->biggest_width] = '\0';
    return(str);
}

char    **get_map(t_map *map, char *filename)
{
    int i;
    int fd;
    int line_len;
    char *line;
    char **buf;

    i = 1;
    fd = open(filename, O_RDONLY);
    buf = (char **)malloc(sizeof(char *) * (map->length + 2 + 1));
    if (!buf)
        return (NULL);
    if (!(buf[0] = create_biggest_buf(map)))
        return (NULL);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        if (i > 1 && (map->width[i] < map->width[i + 1] || map->width[i] < map->width[i - 1]))
        {
            if (map->width[i - 1] > map->width[i + 1])
                buf[i] = add_bigger_buf(-1, map, i, line);
            else
                buf[i] = add_bigger_buf(1, map, i, line);
        }
        else
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
        }
        free(line);
        i++;
    }
    buf[i] = create_biggest_buf(map);
    buf[i + 1] = NULL;
    close(fd);
    return (buf);
}
