/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main->c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student->42->fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:35:10 by ycantin           #+#    #+#             */
/*   Updated: 2024/11/01 14:02:55 by ycantin          ###   ########->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/main.h"

int    init_map(t_map *map, int argc, char **argv)
{
    int fd;
    
    map->player = false;
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (0);
    if (!valid_arguments(argc, argv) || fd < 1)
        return (ft_printf_fd(2, "invalid arguments\n"), 0);
    if (!init_map_and_player(map, argv[1]))
        return(free_array(map->map), free(map->width), 0);
    if (!flood_fill(map))
        return(free_array(map->map), 
                free_bool_array(map->parser.visited, map->length), free(map->width), 0);
    const char *direction_names[] = { "NORTH", "SOUTH", "EAST", "WEST" };
    printf("player initial direction: %s\n", direction_names[map->start_dir]);
    printf ("player x: %d, player y: %d\n", map->x_player, map->y_player);
    for(int i = 0; map->map[i] != NULL; i++)
        printf("%s\n", map->map[i]);
    return (1);
}

void loop(t_game *g)
{
    mlx_loop(g->window.mlx);
}

int main (int argc, char **argv)
{
    t_game *game;
    
    game = malloc (sizeof (t_game));
    if (!game)
        return (1);
    if (!init_map(&game->map, argc, argv))
        return (1);
    game->window.mlx = mlx_init();
	game->window.win = mlx_new_window(game->window.mlx, WIDTH, HEIGHT, "fil de fer");
    free_array(game->map.map);
    free_bool_array(game->map.parser.visited, game->map.length);
    free(game->map.width);
    //mlx_hook(data->win_ptr, 2, (1L << 0), hooks, &data);
	//mlx_hook(data->win_ptr, 17, 0, destroy_data, &data);
	mlx_loop(game->window.mlx);
    //game->loop = loop;
    free(game);
    return (0);
}

//use delta time to make rendering smoother