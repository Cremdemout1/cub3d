/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:46:05 by ycantin           #+#    #+#             */
/*   Updated: 2024/12/18 17:52:12 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void load_textures(t_game **game)
{
    t_texture **textures;
    (*game)->texture_error = 0;
    int i;

    i = 0;
    textures = malloc(sizeof(t_texture ) * 5);
    if (!textures)
        return;
    while (i < 4)
    {
        (*game)->texture_error = i;
        textures[i] = malloc(sizeof(t_texture));
        if (!textures[i])
            return ((*game)->map.parser.error = 1, free(textures));
        textures[i]->img = mlx_xpm_file_to_image((*game)->mlx,
            (*game)->map.texs[i], &textures[i]->width, &textures[i]->height);
        if (!textures[i]->img)
            return ((*game)->map.parser.error = 1, free(textures[i]), free(textures));
        textures[i]->addr = mlx_get_data_addr(textures[i]->img, &textures[i]->bpp,
            &textures[i]->line_len,
            &textures[i]->endian);
        if (!textures[i]->addr)
            return ((*game)->map.parser.error = 1,
                free(textures[i]->img), free(textures[i]), free(textures));
        i++;
    }    
    (*game)->texs = textures;
}

void    load_player_texture(t_game **game)
{
    (*game)->texs[4] = malloc (sizeof (t_texture));
    if (!(*game)->texs[4])
        return (free((*game)->texs));
            (*game)->texs[4]->img = mlx_xpm_file_to_image((*game)->mlx,
                "./includes/textures/player.xpm", &(*game)->texs[4]->width,
                &(*game)->texs[4]->height);
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
                printf("Texture %d loaded success with img at %p\n"
                    , i, game->texs[i]->img);
            }
        }
    }
}
