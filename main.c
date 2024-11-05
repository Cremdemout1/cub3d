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
    map->map = NULL;
    map->width = NULL;
    map->parser.visited = NULL;
    map->parser.error = 0;
    map->N_text = NULL;
    map->S_text = NULL;
    map->W_text = NULL;
    map->E_text = NULL;
    map->floor_color = NULL;
    map->ceiling_color = NULL;

    if (!valid_arguments(argc, argv))
        return (ft_printf_fd(2, "invalid arguments\n"), 0);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (0);
    if (!init_map_and_player(map, argv[1]))
    {
        if (map->map)
            free_array(map->map);
        // if (map->parser.visited) add int array freeer
        if (map->width)
            free(map->width);
        if (map->N_text)
            free(map->N_text);
        if (map->S_text)
            free(map->S_text);
        if (map->W_text)
            free(map->W_text);
        if (map->E_text)
            free(map->E_text);
        if (map->floor_color)
            free(map->floor_color);
        if (map->ceiling_color)
            free(map->ceiling_color);
        return (0);
    }
    flood_fill(map);
    if (map->parser.error == 1)
    {
        if (map->map)
            free_array(map->map);
        // if (map->parser.visited) add int array freeer
        if (map->width)
            free(map->width);
        if (map->N_text)
            free(map->N_text);
        if (map->S_text)
            free(map->S_text);
        if (map->W_text)
            free(map->W_text);
        if (map->E_text)
            free(map->E_text);
        if (map->floor_color)
            free(map->floor_color);
        if (map->ceiling_color)
            free(map->ceiling_color);
        return (0);
    }
    const char *direction_names[] = { "NORTH", "SOUTH", "EAST", "WEST" };
    printf("player initial direction: %s\n", direction_names[map->start_dir]);
    printf ("player x: %d, player y: %d\n", map->x_player, map->y_player);
    printf("start: %d\n", map->map_start);
    printf("length: %d\n", map->length);
    if (map->floor_color)
        printf("floor color: %d,%d,%d\n", map->floor_color[0], map->floor_color[1], map->floor_color[2]);
    if (map->ceiling_color)
        printf("ceiling color: %d,%d,%d\n", map->ceiling_color[0], map->ceiling_color[1], map->ceiling_color[2]);
    printf("NO: %s\n", map->N_text);
    printf("SO: %s\n", map->S_text);
    printf("WE: %s\n", map->W_text);
    printf("EA: %s\n", map->E_text);
    printf("MAP:\n");
    for(int i = 0; map->map[i] != NULL; i++)
        printf("%s\n", map->map[i]);
    if (map->map)
        free_array(map->map);
    // if (map->parser.visited) add int array freeer
    if (map->width)
        free(map->width);
    if (map->N_text)
        free(map->N_text);
    if (map->S_text)
        free(map->S_text);
    if (map->W_text)
        free(map->W_text);
    if (map->E_text)
        free(map->E_text);
    if (map->floor_color)
        free(map->floor_color);
    if (map->ceiling_color)
        free(map->ceiling_color);
    return (1);
}

// void loop(t_game *g)
// {
//     mlx_loop(g->window.mlx);
// }
int destroy(t_game *window)
{
    if (window->win)
    {
        mlx_destroy_window(window->mlx, window->win);
        window->win = NULL;
    }
    if (window->mlx)
    {
        mlx_destroy_display(&window->mlx);
        window->mlx = NULL;
    }
    //free(window->mlx);
    return (0);
}

int exit_t(t_game *g)
{
    free(g);
    exit(0);
    return 1;
}

void    init_window(t_game *g)
{
    g->mlx = mlx_init();
    g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3d");
    if (!g->mlx)
    {
        fprintf(stderr, "Error: MLX initialization failed.\n");
        exit(EXIT_FAILURE);
    }
    mlx_hook(g->win, 17, (1L << 0), exit_t, g);
    // g->window.img = mlx_new_image(g->window.mlx, WIDTH, HEIGHT);
    // g->window.line_len = 
    // g->window.img_addr = mlx_get_data_addr(&g->window.img, &g->window.bits_per_pixel, &g->window.line_len, &game->window.endian);
    
}

int     keybrd_hook(int key, t_game *data)
{
    (void) data;
    if (key == XK_W)
        printf("hey there\n");
    else if (key == XK_ESCAPE)
        destroy(data);
    return (key);
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
    //init_window(game);
    //my_mlx_pixel_put(&game->window, 5, 5, 0x00FF0000);
	//mlx_put_image_to_window(game->window.mlx, game->window.win, game->window.img, 0, 0);
   
    // mlx_hook(game->win, 2, (1L << 0), keybrd_hook, &game);
    // mlx_loop(game->mlx);
    // mlx_destroy_window(game->window.mlx, game->window.win);
    // mlx_destroy_display(game->window.mlx);
    // if (game->map.map)
    //     free_array(game->map.map);
    // if (game->map.parser.visited)
    //     free_bool_array(game->map.parser.visited, game->map.length);
    // free(game->map.width);
    // game->loop = loop;
    // game->loop(game);
    free(game);
    return (0);
}

//use delta time to make rendering smoother


// to do:
// 1. handle info before map: texture paths, floor color and ceiling color. DONE

// 1.2 MAKE lines between last info needed and map not count.               DONE
// 1.3 MAKE SURE IF FOUND BAD INFO AT START, END PROGRAM                    DONE but add check for atoi being given a null value
// 1.3 CHANGE FLOOD FILL TO find error when out of bounds happens           DONE
// 2. get texture paths and ensure their validity.
// 3. ensure validity of floor and ceiling colors.

// 4. open and close window correctly.
// 5. draw each texture in 64 x 64 squares on image. turns out xpms will be assigned to each 1 or 0.
//    give north, south, west, or east value to each wall
// 6. implement 3D aspect.
// 7. implement line drawing(dda) until vertial and horizontal WALL
// 8. add more rays.
// 9. assign height value to walls depending on the length of their ray.