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

void free_resources(t_map *map)
{
    if (map->map)
        free_array(map->map);
    if (map->parser.visited)
        free_bool_array(map->parser.visited, map->length);
    if (map->width)
        free(map->width);
    if (map->texs)
        free_array(map->texs);
    if (map->floor_color)
        free(map->floor_color);
    if (map->ceiling_color)
        free(map->ceiling_color);
}
void load_textures(t_game **game)
{
    t_texture **textures;
    int i;

    i = 0;
    textures = malloc(sizeof(t_texture *) * 4);
    if (!textures)
        return;
    while (i < 4)
    {
        textures[i] = malloc(sizeof(t_texture));
        if (!textures[i])
            return (free(textures));
        textures[i]->img = mlx_xpm_file_to_image((*game)->mlx, (*game)->map.texs[i], &textures[i]->width, &textures[i]->height);
        if (!textures[i]->img)
            return (free(textures[i]), free(textures));
        textures[i]->addr = mlx_get_data_addr(
            textures[i]->img,
            &textures[i]->bpp,
            &textures[i]->line_len,
            &textures[i]->endian);
        if (!textures[i]->addr)
            return (free(textures[i]->img), free(textures[i]), free(textures));
        i++;
    }
    printf("%d  %d\n", textures[i - 1]->width, textures[i - 1]->height);
    (*game)->texs = textures;
}

void draw_map(t_game *game)
{
    int x, y;
    int map_x, map_y;

    for (map_y = 0; map_y < game->map.length; map_y++) {
        for (map_x = 0; map_x < game->map.width[map_y]; map_x++) {
            if (game->map.map[map_y][map_x] == '1') {
                x = map_x * XPM_X;
                y = map_y * XPM_Y;
                if (game->map.map && game->map.map[map_y][map_x] == '1') {
                    mlx_put_image_to_window(game->mlx, game->win, game->texs[0]->img, x, y);  // North wall
                }
            }
        }
    }
}


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
        return (0);
    if (!init_map_and_player(map, argv[1]))
        return (0);
    flood_fill(map);
    if (map->parser.error == 1)
        return (0);
    //const char *direction_names[] = { "NORTH", "SOUTH", "EAST", "WEST" };
    // printf("player initial direction: %s\n", direction_names[map->start_dir]);
    // printf ("player x: %d, player y: %d\n", map->x_player, map->y_player);
    // printf("start: %d\n", map->map_start);
    // printf("length: %d\n", map->length);
    // if (map->floor_color)
    //     printf("floor color: %d,%d,%d\n", map->floor_color[0], map->floor_color[1], map->floor_color[2]);
    // if (map->ceiling_color)
    //     printf("ceiling color: %d,%d,%d\n", map->ceiling_color[0], map->ceiling_color[1], map->ceiling_color[2]);
    // for(int i = 0; map->texs[i] != NULL; i++)
    //     printf("%s\n", map->texs[i]);
    // printf("MAP:\n");
    // for(int i = 0; map->map[i] != NULL; i++)
    //     printf("%s\n", map->map[i]);
    return (1);
}

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
    free_resources(&g->map);
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
    g->loop = loop;
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

void test_textures(t_game *game) {
    if (!game->texs) {
        printf("Textures array is NULL\n");
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (game->texs[i] == NULL) {
            printf("Texture %d is NULL\n", i);
        } else {
            if (game->texs[i]->img == NULL) {
                printf("Texture %d image is NULL\n", i);
            } else {
                printf("Texture %d loaded successfully with image at %p\n", i, game->texs[i]->img);
            }
        }
    }
}


int main (int argc, char **argv)
{
    t_game *game;
    
    game = malloc (sizeof (t_game));
    if (!game)
        return (1);
    if (!init_map(&game->map, argc, argv))
        return (free(game), 1);
    init_window(game);
    load_textures(&game);
    test_textures(game);
    draw_map(game);
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
    game->loop(game);
    free_resources(&game->map);
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