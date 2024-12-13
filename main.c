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

void load_textures(t_game **game)
{
    t_texture **textures;
    int i;

    i = 0;
    textures = malloc(sizeof(t_texture ) * 5);
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
    (*game)->texs = textures;
}

void    load_player_texture(t_game **game)
{
    (*game)->texs[4] = malloc (sizeof (t_texture));
    if (!(*game)->texs[4])
        return (free((*game)->texs));
            (*game)->texs[4]->img = mlx_xpm_file_to_image((*game)->mlx, "./player.xpm", &(*game)->texs[4]->width, &(*game)->texs[4]->height);
        if (!(*game)->texs[4]->img)
            return (free((*game)->texs[4]), free((*game)->texs));
    (*game)->texs[4]->addr = mlx_get_data_addr(
        (*game)->texs[4]->img,
        &(*game)->texs[4]->bpp,
        &(*game)->texs[4]->line_len,
        &(*game)->texs[4]->endian);
    if (!(*game)->texs[4]->addr)
        return (free((*game)->texs[4]->img), free((*game)->texs));
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
        return (free_array(map->map), free_bool_array(map->parser.visited, map->length)
            , free(map->ceiling_color), free(map->floor_color)
            , free(map->width), free_array(map->texs), 0);
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

int keybrd_hook(int key, t_game **game)
{
    if (key == 65307)
        exit_t(*game);
    if (key >= 0 && key < 280)
        (*game)->keys[key] = true;
    return key;
}

int keyrelease_hook(int key, t_game **game)
{
    printf("off: %d\n", key);
    if (key >= 0 && key < 280)
        (*game)->keys[key] = false;
    return key;
}

int all_moves(t_game **game, int keycode)
{
    if ((*game)->keys[119] || (*game)->keys[115])
        player_move(*game);
    if ((*game)->keys[100] || (*game)->keys[97])
        player_rotate(*game);
    return (keycode);
}

void    init_window(t_game **g)
{
    // add second window minimap:

    // (*g)->scdmlx = mlx_init();
    // (*g)->scdwin = mlx_new_window((*g)->scdmlx, 500, 500, "2D map");
    //(*g)->img_ptr = mlx_new_image((*g)->mlx, WIDTH, HEIGHT);
    ft_memset((*g)->keys, false, 280);
    (*g)->mlx = mlx_init();
    (*g)->win = mlx_new_window((*g)->mlx, WIDTH, HEIGHT, "cub3d");
    if (!(*g)->mlx)
    {
        fprintf(stderr, "Error: MLX initialization failed.\n");
        exit(EXIT_FAILURE);
    }
    (*g)->loop = loop;
    mlx_hook((*g)->win, 2, (1L << 0), keybrd_hook, g);
    mlx_hook((*g)->win, 3, (1L << 1), keyrelease_hook, g);
    mlx_hook((*g)->win, 17, (1L << 0), exit_t, g);
    mlx_do_key_autorepeatoff((*g)->mlx);
    mlx_loop_hook((*g)->mlx, all_moves, g);
}

void test_textures(t_game *game)
{
    if (!game->texs) {
        printf("Textures array is NULL\n");
        return;
    }

    for (int i = 0; i < 5; i++) {
        if (game->texs[i] == NULL) {
            printf("Texture %d is NULL\n", i);
        } else {
            if (game->texs[i]->img == NULL) {
                printf("Texture %d img is NULL\n", i);
            } else {
                printf("Texture %d loaded successnormalizedY with img at %p\n", i, game->texs[i]->img);
            }
        }
    }
}

void	img_placeholder(t_game **game)
{
	(*game)->img.bits_per_pixel = 32;
	(*game)->img.line_len = WIDTH * 4;
	(*game)->img.endian = 0;
	(*game)->img_ptr = mlx_new_image((*game)->mlx, WIDTH, HEIGHT);
	(*game)->img.img_pixel_ptr = mlx_get_data_addr((*game)->img_ptr,
			&(*game)->img.bits_per_pixel, &(*game)->img.line_len,
			&(*game)->img.endian);
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
    load_player_texture(&game);
    img_placeholder(&game);
    init_player_info(game);
    //test_textures(game); 
    //draw_map(game); // for minimap
    cast_all_rays(game);
    game->loop(game);
    return (0);
}

//use delta time to make rendering smoother


// to do:
// 1. handle info before map: texture paths, floor color and ceiling color. DONE
// 1.2 MAKE lines between last info needed and map not count.               DONE
// 1.3 MAKE SURE IF FOUND BAD INFO AT START, END PROGRAM                    DONE but add check for atoi being given a null value
// 1.3 CHANGE FLOOD FILL TO find error when out of bounds happens           DONE
// 3. ensure validity of floor and ceiling colors.                          DONE
// 4. open and close window correctly.                                      DONE
// 5. draw each texture in 64 x 64 squares on img. turns out xpms will be assigned to each 1 or 0.
// 6. implement 3D aspect.                                                  DONE
// 7. implement line drawing(dda) until vertial and horizontal WALL         DONE
// 8. add more rays.                                                        DONE
// 9. assign height value to walls depending on the length of their ray.    DONE

// URGENT: FIX X BUTTON
// 1. give north, south, west, or east value to each wall    DONE               NOT NEEDED
// 2. get texture paths and ensure their validity.
// 3. make the vertical drawing draw ceiling and floor depending on if its on top half or  bottom half instead of separate function
// 4. make movement work                                     DONE
// 5. draw textures on 3D walls                              DONE
// 6. make minimap inside normal map
// 7. test my parser
//    have fun ;)