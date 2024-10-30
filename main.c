/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:35:10 by ycantin           #+#    #+#             */
/*   Updated: 2024/10/30 22:32:28 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int main (int argc, char **argv)
{
    int fd;
    t_map map;
    
    map.player = false;
    fd = open(argv[1], O_RDONLY);
    if (!valid_arguments(argc, argv) || fd < 1)
        return (ft_printf_fd(2, "invalid arguments\n"), 1);
    if (!init_map_and_player(&map, fd))
        return (1);
    /* if (!flood_fill(&map))
    {
        free_array(map.map);
        free_bool_array(map.parser.visited, map.length);
        free(map.width);
        return(1);
    } */
    free_array(map.map);
    free_bool_array(map.parser.visited, map.length);
    free(map.width);
    return (0);
}

//use delta time to make rendering smoother