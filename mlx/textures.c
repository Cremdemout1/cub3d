/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 13:12:52 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 15:10:33 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	assign_texture_values(t_game **game, t_texture **texture, int i)
{
	*texture = malloc(sizeof(t_texture));
	if (!*texture)
		return (1);
	(*texture)->img = mlx_xpm_file_to_image((*game)->mlx,
			(*game)->map.texs[i], &(*texture)->width,
			&(*texture)->height);
	if (!(*texture)->img)
		return (2);
	(*texture)->addr = mlx_get_data_addr((*texture)->img,
			&(*texture)->bpp, &(*texture)->line_len,
			&(*texture)->endian);
	if (!(*texture)->addr)
		return (3);
	return (0);
}

void	free_loaded_textures(t_texture **textures, int count, void *mlx)
{
	int	i;

	i = 0;
	if (!textures)
		return ;
	while (i < count)
	{
		if (textures[i])
		{
			if (textures[i]->img)
				mlx_destroy_image(mlx, textures[i]->img);
			free(textures[i]);
		}
		i++;
	}
	free(textures);
}

void	load_textures(t_game **game)
{
	t_texture	**textures;
	int			i;
	int			error;

	textures = malloc(sizeof(t_texture *) * 5);
	if (!textures)
		return ;
	i = 0;
	while (i < 4)
	{
		textures[i] = NULL;
		error = assign_texture_values(game, &textures[i], i);
		if (error != 0)
		{
			printf("%d\n", error);
			(*game)->map.parser.error = 1;
			free_loaded_textures(textures, i + 1, (*game)->mlx);
			return ;
		}
		i++;
	}
	textures[4] = NULL;
	(*game)->texs = textures;
}

void	load_player_texture(t_game **game)
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

void	test_textures(t_game *game)
{
	int	i;

	i = 0;
	if (!game->texs)
	{
		printf("Textures array is NULL\n");
		return ;
	}
	while (i < 5)
	{
		if (game->texs[i] == NULL)
			printf("Texture %d is NULL\n", i);
		else
		{
			if (game->texs[i]->img == NULL)
				printf("Texture %d img is NULL\n", i);
			else
				printf("Texture %d loaded success with img at %p\n",
					i, game->texs[i]->img);
		}
		i++;
	}
}
