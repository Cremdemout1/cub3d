/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:23:47 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/15 14:40:24 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

bool	valid_arguments(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2 || !argv[1] || !argv[1][0])
		return (false);
	while (argv[1][i] && argv[1][i] != '.')
		i++;
	if (ft_strcmp(argv[1] + i, ".cub") != 0)
		return (false);
	return (true);
}

bool	valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ');
}

void	free_str_textures(t_map *map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map->texs[i])
			free(map->texs[i]);
		i++;
	}
	free(map->texs);
}

void	free_starting_info(t_map *map)
{
	free_str_textures(map);
	free(map->ceiling_color);
	free(map->floor_color);
}

bool	return_value(t_variables *purse)
{
	if (purse->is_empty)
		return (ft_printf_fd(2, "Error\nMap empty\n"), false);
	if (purse->error == 1)
		return (ft_printf_fd(2, "Error\nNon conformative character\n"), false);
	if (purse->count < 1)
		return (ft_printf_fd(2, "Error\nNo player found\n"), false);
	else if (purse->count == 1)
		return (true);
	return (ft_printf_fd(2, "Error\nToo many players found\n"), false);
}
