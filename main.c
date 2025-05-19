/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:13:47 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 15:13:49 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int    init_map(t_map *map, int argc, char **argv)
{
    int fd;
    
    map->player = false;
    map->map = NULL;
    map->width = NULL;
    map->parser.visited = NULL;
    map->parser.error = 0;
    map->texs = NULL;
    map->floor_color = NULL;
    map->ceiling_color = NULL;
    if (!valid_arguments(argc, argv))
        return (ft_printf_fd(2, "invalid arguments\n"), 0);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (close(fd), 0);
    if (!init_map_and_player(map, argv[1]))
        return (close(fd), 0);
    flood_fill(map);
    if (map->parser.error == 1)
        return (close(fd), free_array(map->map), 
            free_bool_array(map->parser.visited, map->length)
            , free(map->ceiling_color), free(map->floor_color)
            , free(map->width), free_array(map->texs), 0);
    return (close(fd), 1);
}

void    loop(t_game *g)
{
    if (g->mlx)
        mlx_loop(g->mlx);
}

int main (int argc, char **argv)
{
    t_game *game;
    
    game = malloc (sizeof (t_game));
    if (!game)
        return (1);
    if (!init_map(&game->map, argc, argv))
        return (free(game), 1);
    init_window(&game);
    load_textures(&game);
    if (game->map.parser.error)
        return(game_error(&game), ft_printf_fd(2, "Error\nTextures invalid\n"), 1); // take care of memory allocation
    load_player_texture(&game);
    img_placeholder(&game);
    init_player_info(game);
    gettimeofday(&game->last_time, NULL);
    cast_all_rays(game);
    game->loop(game);
    return (0);
}
