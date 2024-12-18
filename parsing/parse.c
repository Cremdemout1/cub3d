/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:35 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/18 12:20:59 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

bool    valid_arguments(int argc, char **argv)
{
    int i;

    i = 0;
    if (argc != 2 || !argv[1] || !argv[1][0])
        return (false);
    while (argv[1][i] && argv[1][i] != '.')
        i++;
    if (ft_strcmp(argv[1] + i, ".cub") != 0)
        return (false);
    return (true);
}

bool valid_map_char(char c)
{
    return (c == '1' || c == '0' || c == 'N'
            || c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

bool found_player(t_map *info)
{
    int     x;
    int     y;
    int     count;
    int     error;
    int     is_empty;
        
    y = 0;
    error = 0;
    count = 0;
    is_empty = true;
    while (info->map[y])
    {
        x = 0;
        while (info->map[y][x])
        {
            char    cur;
            cur = info->map[y][x];
            if (cur != '\n' && cur != '\0' && cur != '\t' && cur != ' ')
                is_empty = false;    
            if (!valid_map_char(cur))
                error = 1;
            else
            {
                if (valid_map_char(cur) &&  cur != '0' && cur != '1' && cur != ' ')
                {
                    player_start_info(info, cur, x, y);
                    count++;
                }
            }
            x++;
        }
        y++;
    }
    if (is_empty)
        return (ft_printf_fd(2, "Error\nMap empty\n"), false);
    if (error == 1)
        return (ft_printf_fd(2, "Error\nNon conformative character\n"), false);
    if (count < 1)
        return (ft_printf_fd(2, "Error\nNo player found\n"), false);
    else if(count == 1)
        return (true);
    return (ft_printf_fd(2, "Error\nToo many players found\n"), false);
}

int    valid_textures(t_map *map)
{
    int i;
    int j;
    int fd;

    i = 0;   
    while (i < 4)
    {
        j = 0;
        while (map->texs[i][j])
           j++;
        while(map->texs[i][j] != '.')
            j--;
        fd = open(map->texs[i], O_RDONLY);
        if (fd < 0 || ft_strncmp(map->texs[i] + j + 1, "xpm", 3) || !ft_isalnum(map->texs[i][j - 1]))
        {
            ft_printf_fd(2, "Error\nInvalid texture: %s\n", map->texs[i]);
            return (0);
        }
        close(fd);
        i++;
    }
    return (1);
}

void    free_str_textures(t_map *map)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (map->texs[i])
            free(map->texs[i]);
        i++;
    }
    free(map->texs);
}

void    free_starting_info(t_map *map)
{
    free_str_textures(map);
    free(map->ceiling_color);
    free(map->floor_color);
}

bool    init_map_and_player(t_map *map_info, char *filename)
{
    char **map;
    
    if (get_starting_info(map_info, filename) != 0 || map_info->parser.error)
        return (free_starting_info(map_info), 
            ft_printf_fd(2, "Error\nCouldn't find required information\n"), 
            false);
    if (!valid_textures(map_info))
        return (free_starting_info(map_info), false);
    get_length(map_info, filename);
    get_widths(map_info, filename);
    map = get_map(map_info, filename);
    if (!map)
        return (free_starting_info(map_info), free(map_info->width), false);
        // return (free_starting_info(map_info),
        //     free_array(map), free(map_info->width), ft_printf_fd(2, "Error\nMap creation error\n"), false);
    map_info->map = map;
    if (!found_player(map_info))
        return (free_starting_info(map_info), free(map_info->width), 
            free_array(map_info->map)/* , 
                ft_printf_fd(2, "Error\nInitiation error\n") */, false);
    return (true);
}
