/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:35 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/04 05:11:27 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

// char    *add_bigger_buf(int decider, t_map *map, int i, char *line)
// {
//     int len;
//     int size;
//     char *str;
    
//     size = ft_strlen(line);
//     if (decider == -1)
//         len = map->width[i - 1];
//     else if (decider == 1)
//         len = map->width[i + 1];
//     str = malloc(sizeof(char) * (len + 2));
//     if (!str)
//         return (NULL);
//     str[0] = ' ';
//     ft_strcpy(str + 1, line);
    
//     if (line[size - 1] !='\n')
//     {
//         while (size < (len - 1))
//             str[size++] = ' ';
//         str[size + 1] = ' ';
//         str[size + 2] = '\0';
//     }
//     else
//     {    
//         while ((size) < len)
//             str[size++] = ' ';
//         str[size] = ' ';
//         str[size + 1] = '\0';
//     }
//     return (str);
// }


// char *create_biggest_buf(t_map *map)
// {
//     char *str;
    
//     str = (char *)malloc(sizeof(char) * (map->biggest_width + 1));
//     if (!str)
//         return (NULL);
//     ft_memset(str, ' ', map->biggest_width);
//     str[map->biggest_width] = '\0';
//     return(str);
// }

int     is_empty(char *str)
{
    int i;

    i = 0;
    if (!str[0])
        return (1);
    while (str[i])
        i++;
    if (str[i - 1] == '\0' || str[i - 1] == '\n' || i == 0 || i == 1)
        return (1);
    return (0);
}

// char    **get_map(t_map *map, char *filename)
// {
//     int i;
//     int fd;
//     int line_len;
//     char *line;
//     char **buf;

//     i = 1;
//     fd = open(filename, O_RDONLY);
//     buf = (char **)malloc(sizeof(char *) * (map->length + 2 + 1));
//     if (!buf)
//         return (NULL);

//     if (!(buf[0] = create_biggest_buf(map)))
//         return (NULL);
//     while (1)
//     {
//         line = get_next_line(fd);
//         if (!line)
//             break ;
//         if (i > 1 && (map->width[i] < map->width[i + 1] || map->width[i] < map->width[i - 1]))
//         {
//             if (map->width[i - 1] > map->width[i + 1])
//                 buf[i] = add_bigger_buf(-1, map, i, line);
//             else
//                 buf[i] = add_bigger_buf(1, map, i, line);
//         }
//         else
//         {
//             line_len = ft_strlen(line);
//             if (line[line_len - 1] == '\n')
//                 line_len--;
//             buf[i] = (char *)malloc(sizeof(char) * (line_len + 2 + 1)); // 2 extra for spaces
//             if (!buf[i])
//                 return NULL;
//             buf[i][0] = ' ';
//             ft_strcpy(buf[i] + 1, line);
//             buf[i][line_len + 1] = ' ';
//             buf[i][line_len + 2] = '\0';
//         }
//         free(line);
//         i++;
//     }
//     buf[i] = create_biggest_buf(map);
//     buf[i + 1] = NULL;
//     close(fd);
//     return (buf);
// }

// int get_starting_info(t_map *map, char *filename) {
//     int i = 0;
//     int found = 0;
//     int fd;
//     char *line;
//     int error[4] = {0, 0, 0, 0}; // Track texture assignments

//     fd = open(filename, O_RDONLY);
//     if (fd < 0) {
//         perror("Error opening file");
//         return 1; // Return error if file cannot be opened
//     }

//     while (1) {
//         line = get_next_line(fd);
//         if (!line) {
//             break; // Exit if end of file is reached
//         }

//         // Skip leading whitespace
//         int j = 0;
//         while (line[j] == ' ' || line[j] == '\t') {
//             j++;
//         }

//         // Check for empty line
//         if (line[j] == '\0') {
//             free(line);
//             i++;
//             continue;
//         }

//         // Texture definitions
//         if (ft_strncmp(line + j, "NO", 2) == 0) {
//             if (error[0]) {
//                 free(line);
//                 close(fd);
//                 return ft_printf_fd(2, "Error: same cardinal texture found more than once\n"), 1;
//             }
//             map->N_text = ft_strdup(line + j + 3); // Skip "NO "
//             error[0] = 1;
//             i++;
//             continue ;
//         } else if (ft_strncmp(line + j, "SO", 2) == 0) {
//             if (error[1]) {
//                 free(line);
//                 close(fd);
//                 return ft_printf_fd(2, "Error: same cardinal texture found more than once\n"), 1;
//             }
//             map->S_text = ft_strdup(line + j + 3); // Skip "SO "
//             error[1] = 1;
//             i++;
//             continue ;
//         } else if (ft_strncmp(line + j, "WE", 2) == 0) {
//             if (error[2]) {
//                 free(line);
//                 close(fd);
//                 return ft_printf_fd(2, "Error: same cardinal texture found more than once\n"), 1;
//             }
//             map->W_text = ft_strdup(line + j + 3); // Skip "WE "
//             error[2] = 1;
//             i++;
//             continue ;
//         } else if (ft_strncmp(line + j, "EA", 2) == 0) {
//             if (error[3]) {
//                 free(line);
//                 close(fd);
//                 return ft_printf_fd(2, "Error: same cardinal texture found more than once\n"), 1;
//             }
//             map->E_text = ft_strdup(line + j + 3); // Skip "EA "
//             error[3] = 1;
//             i++;
//             continue ;
//         }
//             free(line);
//             //i++;
//         if (error[0] && error[1] && error[2] && error[3]) {
//             found = 1;
//             break; // Exit after finding the start of the map
//         }
//         i++;
//     }
//     if (found)
//         map->map_start = i; // Mark the start of the map
//     else
//         map->map_start = 0;
//     close(fd);
//     return 0; // Return success
// }

int get_starting_info(t_map *map, char *filename) 
{
    int i = 0;
    int fd;
    char *line;
    int found[6] = {0, 0, 0, 0, 0, 0}; // Track texture assignments
    int error = 0;

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return 1; // Return error if file cannot be opened
    }

    while (1)
    {
        line = get_next_line(fd);
        if (!line) {
            break; // Exit if end of file is reached
        }
        // Skip leading whitespace
        int j = 0;
        while (line[j] == ' ' || line[j] == '\t') {
            j++;
        }

        // Check for empty line
        if (line[j] == '\0') {
            free(line);
            i++;
            continue;
        }

        // Texture definitions
        if (ft_strncmp(line + j, "NO", 2) == 0 && !found[0]) { // remove last char if its \n
            map->N_text = ft_strdup(line + j + 3); // Skip "NO " 
            found[0] = 1;
        } else if (ft_strncmp(line + j, "SO", 2) == 0 && !found[1]) {
            map->S_text = ft_strdup(line + j + 3); // Skip "SO "
            found[1] = 1;
        } else if (ft_strncmp(line + j, "WE", 2) == 0 && !found[2]) {
            map->W_text = ft_strdup(line + j + 3); // Skip "WE "
            found[2] = 1;
        } else if (ft_strncmp(line + j, "EA", 2) == 0 && !found[3]) {
            map->E_text = ft_strdup(line + j + 3); // Skip "EA "
            found[3] = 1;
        } else if (ft_strncmp(line + j, "F", 1) == 0 && !found[4]) {
            map->floor_color = ft_strdup(line + j + 2); // Skip "EA "
            found[4] = 1;
        } else if (ft_strncmp(line + j, "C", 1) == 0 && !found[5]) {
            map->ceiling_color = ft_strdup(line + j + 2); // Skip "EA "
            found[5] = 1;
        } 
        else if(found[0] && found[1] && found[2] && found[3] && found[4] && found[5] && !error)
        {
                free(line);
                close(fd);
                map->map_start = i;
                return (0);
        }
        free(line);
        i++;
    }
    // if (error)
    //     return (ft_printf_fd(2, "Error: found non-standard information: "), -1);
    map->map_start = i;
    if (i == 0)
        return (-1);
    close(fd);
    return (-1);
}

char    **get_map(t_map *map, char *filename)
{
    int i;
    int fd;
    char *line;
    char **buf;

    i = 0;
    fd = open(filename, O_RDONLY);
    i = 0;
    while (i < map->map_start)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        free(line);
        i++;
    }
    i = 0;
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
    close(fd);
    return (buf);
}
