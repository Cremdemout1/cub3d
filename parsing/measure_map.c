/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:15:59 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 15:16:01 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	get_length(t_map *map, char *filename)
{
	t_variables	purse;

	purse.fd = open(filename, O_RDONLY);
	purse.y = 0;
	while (purse.y < map->map_start)
	{
		purse.line = get_next_line(purse.fd);
		if (!purse.line)
			break ;
		free(purse.line);
		purse.y++;
	}
	purse.y = 0;
	while (1)
	{
		purse.line = get_next_line(purse.fd);
		if (!purse.line)
			break ;
		purse.y++;
		free(purse.line);
	}
	map->length = purse.y;
	close(purse.fd);
}

int	assign_purse_values(t_variables *purse, int map_length,
		char *filename, int map_start)
{
	purse->y = 0;
	purse->size = 0;
	purse->fd = open(filename, O_RDONLY);
	purse->array = malloc (sizeof(int) * map_length);
	if (!purse->array)
		return (0);
	while (purse->y++ < map_start)
	{
		purse->line = get_next_line(purse->fd);
		if (!purse->line)
			break ;
		free(purse->line);
	}
	return (1);
}

void	get_widths(t_map *map, char *filename)
{
	t_variables	purse;

	if (!assign_purse_values(&purse, map->length, filename, map->map_start))
		return ;
	purse.y = 0;
	while (1)
	{
		purse.line = get_next_line(purse.fd);
		if (!purse.line)
			break ;
		purse.array[purse.y] = ft_strlen(purse.line);
		if (purse.array[purse.y] > purse.size)
			purse.size = purse.array[purse.y];
		purse.y++;
		free(purse.line);
	}
	while (purse.y < map->length)
    {
        purse.array[purse.y] = 0;
        purse.y++;
    }
	map->width = purse.array;
	map->max_width = purse.size;
	close(purse.fd);
}


void	player_start_info(t_map *info, char dir, int x, int y)
{
	if (dir == 'N')
		info->facing = NORTH;
	else if (dir == 'S')
		info->facing = SOUTH;
	else if (dir == 'W')
		info->facing = WEST;
	else if (dir == 'E')
		info->facing = EAST;
	info->x_player = x;
	info->y_player = y;
	info->dir = dir;
}
