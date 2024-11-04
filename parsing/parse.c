/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:43:35 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/04 04:40:35 by ycantin          ###   ########.fr       */
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
    if (ft_strcmp(argv[1] + i, ".cub") != 0) //works?? huh
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
        
    y = 0;
    error = 0;
    count = 0;
    while (info->map[y])
    {
        x = 0;
        //printf("%s\n", info->map[y]); 
        while (info->map[y][x])
        {
            char    cur;
            cur = info->map[y][x];
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
    if (error == 1)
        return (ft_printf_fd(2, "non conformative character: "), false);
    if (count < 1)
        return (ft_printf_fd(2, "no player found: "), false);
    else if(count == 1)
        return (true);
    return (ft_printf_fd(2, "too many players found: "), false);
}

bool    init_map_and_player(t_map *map_info, char *filename)
{
    char **map;
    
    if (get_starting_info(map_info, filename) != 0)
        return (ft_printf_fd(2, "couldnt find info needed\n"), false);
    get_length(map_info, filename);
    get_widths(map_info, filename);
    map = get_map(map_info, filename);
    if (!map)
        return (ft_printf_fd(2, "map creation error\n"), false);
    map_info->map = map;
    for(int i = 0; map_info->map[i] != NULL; i++)
        printf("%s\n", map_info->map[i]);
    if (!found_player(map_info))
        return (ft_printf_fd(2, "initiation error\n"), false);
    //initialize_visit_state(map_info);
    return (true);
}
