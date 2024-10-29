/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:35:10 by ycantin           #+#    #+#             */
/*   Updated: 2024/10/29 19:56:36 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int main (int argc, char **argv)
{
    int fd;
    t_map map;
    
    fd = open(argv[1], O_RDONLY);
    if (!valid_arguments(argc, argv) || fd < 1)
        return (printf("invalid arguments\n"), 1);
    flood_fill(&map, fd);
    // printf("%d\n", map.length);
    close(fd);
    return (0);
}

//use delta time to make rendering smoother