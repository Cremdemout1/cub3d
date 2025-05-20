/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:12:32 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/20 18:24:35 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	inner_loop(t_map *info, t_variables *purse)
{
	char	cur;

	while (info->map[purse->y][purse->x])
	{
		cur = info->map[purse->y][purse->x];
		if (cur != '\n' && cur != '\0' && cur != '\t' && cur != ' ')
			purse->is_empty = false;
		if (!valid_map_char(cur))
			purse->error = 1;
		else
		{
			if (valid_map_char(cur) && cur != '0' && cur != '1' && cur != ' ')
			{
				player_start_info(info, cur, purse->x, purse->y);
				purse->count++;
			}
		}
		purse->x++;
	}
}

bool	found_player(t_map *info)
{
	t_variables	purse;

	purse.y = 0;
	purse.error = 0;
	purse.count = 0;
	purse.is_empty = true;
	while (info->map[purse.y])
	{
		purse.x = 0;
		inner_loop(info, &purse);
		purse.y++;
	}
	return (return_value(&purse));
}

int	valid_textures(t_map *map)
{
	int	i;
	int	j;
	int	fd;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (map->texs[i][j])
			j++;
		while (map->texs[i][j] != '.')
			j--;
		fd = open(map->texs[i], O_RDONLY);
		if (fd < 0 || ft_strncmp(map->texs[i] + j + 1, "xpm", 3)
			|| !ft_isalnum(map->texs[i][j - 1]))
		{
			ft_printf_fd(2, "Error\nInvalid texture: %s\n", map->texs[i]);
			return (0);
		}
		close(fd);
		i++;
	}
	return (1);
}

bool	init_map_and_player(t_map *map_info, char *filename)
{
	char	**map;

	if (get_starting_info(map_info, filename) != 0 || map_info->parser.error)
		return (free_starting_info(map_info),
			ft_printf_fd(2, "Error\nCouldn't find required information\n"),
			false);
	if (!valid_textures(map_info))
		return (free_starting_info(map_info), false);
	get_length(map_info, filename);
	get_widths(map_info, filename);
	map = get_map(map_info, filename);
	if (!map)
		return (free_starting_info(map_info), free(map_info->width), false);
	map_info->map = map;
	if (!found_player(map_info))
		return (free_starting_info(map_info), free(map_info->width),
			free_array(map_info->map), false);
	return (true);
}
