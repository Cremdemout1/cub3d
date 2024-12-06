/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:35 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/06 14:22:52 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

bool    is_valid_file(char *file)
{
    if (access(file, F_OK) == 0)
        return (true);
    return (false);
}

int is_empty(char *str)
{
    int i;
    
    i = 0;
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    if (str[i] == '\0')
        return (1);
    return(0);
}

void    handle_texture(t_map *map, char *texture, int *found, int dir)
{
    int len;

    len = ft_strlen(texture);
    if (texture[len - 1] == '\n')
        texture[len - 1] = '\0';
    if (dir == 1)
        map->texs[0] = ft_strdup(texture + 3);
    else if (dir == 2)
        map->texs[1] = ft_strdup(texture + 3);
    else if (dir == 3)
        map->texs[2] = ft_strdup(texture + 3);
    else if (dir == 4)
        map->texs[3] = ft_strdup(texture + 3);
    *found = 1;
}

bool    has_non_num_val(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (!str[i])
            return (false);
        if (!(str[i] >= '0' && str[i] <= '9') && str[i] != ' ' && str[i] != '\n')
            return (/* printf("error found:%c\n", str[i]), */ true);
        i++;
    }
    return (false);
}

int    handle_color(t_map *map, char *color, int *found, int type)
{
    char **split;
    int *rgb;
    int i;
    
    i = 0;
    split = ft_split(color, ',');
    if(!split)
        return (ft_printf_fd(2, "Error\n"), 0);
    if (count_strings(split) != 3)
        return (ft_printf_fd(2, "color unavailable: wrong count\n"), free_array(split), 0);
    rgb = malloc(sizeof (int) * 3);
    while (split[i])
    {
        rgb[i] = ft_atoi(split[i]);
        if (rgb[i] > 255 || rgb[i] < 0 || has_non_num_val(split[i]))
            return (ft_printf_fd(2, "color unavailable: wrong value\n"), free(rgb), free_array(split), 0);
        i++;
    }
    free_array(split);
    if (type == 1)
        map->floor_color = rgb;
    else
        map->ceiling_color = rgb;
    return (*found = 1, 1);
}

int get_starting_info(t_map *map, char *filename) 
{
    int i;
    int j;
    int fd;
    char *line;
    int found[6] = {0, 0, 0, 0, 0, 0}; // Track texture assignments
    int error;

    i = 0;
    error = 0;
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1; // Return error if file cannot be opened
    }
    map->texs = malloc(sizeof (char *) * 5);
    if (!map->texs)
        return (-1);
    while (i < 5)
        map->texs[i++] = NULL;
    i = 0;  
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        j = 0;
        while (line[j] == ' ' || line[j] == '\t') 
            j++;
        if (line[j] == '\0') {
            free(line);
            i++;
            continue;
        }
        if (ft_strncmp(line + j, "NO", 2) == 0 && !found[0]) 
            handle_texture(map, line, &found[0], 1);
        else if (ft_strncmp(line + j, "SO", 2) == 0 && !found[1])
            handle_texture(map, line, &found[1], 2);
        else if (ft_strncmp(line + j, "WE", 2) == 0 && !found[2]) 
            handle_texture(map, line, &found[2], 3);
        else if (ft_strncmp(line + j, "EA", 2) == 0 && !found[3])
            handle_texture(map, line, &found[3], 4);
        else if (ft_strncmp(line + j, "F", 1) == 0 && !found[4]) 
        {
            if (!handle_color(map, line + 2, &found[4], 1))
                return (free(line), -1);
        }
        else if (ft_strncmp(line + j, "C", 1) == 0 && !found[5]) 
        {
            if (!handle_color(map, line + 2, &found[5], 2))
                return (free(line), -1);
        }
        else if (map->parser.error)
            return (-1);
        else if(found[0] && found[1] && found[2] && found[3] && found[4] && found[5] && !error)
        {
            free(line);
            while (1)
            {
                line = get_next_line(fd);
                if (!line)
                    break;
                if (!is_empty(line)) 
                {
                    free(line);
                    break;
                }
                i++;
                free(line);
            }
            map->map_start = i;
            close(fd);
            return (0);
        }
        free(line);
        i++;
    }
    map->map_start = i;
    if (i == 0)
        return (-1);
    close(fd);
    return (-1);
}

void    skip_initial_lines(t_map *map, int fd)
{
    int i;
    char *line;

    i = 0;
    while (i < map->map_start)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        free(line);
        i++;
    }
}

char    **get_map(t_map *map, char *filename)
{
    int i;
    int fd;
    char *line;
    char **buf;

    i = 0;
    fd = open(filename, O_RDONLY);
    skip_initial_lines(map, fd);
    buf = malloc(sizeof(char *) * (map->length + 1));
    if (!buf)
        return (NULL);
    while (i < map->length)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        buf[i] = ft_strdup(line);
        int len = ft_strlen(buf[i]);
        if (len > 0 && buf[i][len - 1] == '\n')
            buf[i][len - 1] = '\0';
        free(line);
        i++;
    }
    buf[i] = NULL;
    return (close(fd), buf);
}
