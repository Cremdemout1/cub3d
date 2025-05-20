/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:26:09 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/20 18:43:24 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	handle_colors_and_textures(t_variables *p, int *found, t_map *map)
{
	if (ft_strncmp(p->line + p->j, "NO", 2) == 0 && !found[0])
		handle_texture(map, p->line, &found[0], 1);
	else if (ft_strncmp(p->line + p->j, "SO", 2) == 0 && !found[1])
		handle_texture(map, p->line, &found[1], 2);
	else if (ft_strncmp(p->line + p->j, "WE", 2) == 0 && !found[2])
		handle_texture(map, p->line, &found[2], 3);
	else if (ft_strncmp(p->line + p->j, "EA", 2) == 0 && !found[3])
		handle_texture(map, p->line, &found[3], 4);
	else if (ft_strncmp(p->line + p->j, "F ", 2) == 0 && !found[4])
	{
		if (!handle_color(map, p->line + 2, &found[4], 1))
			return (0);
	}
	else if (ft_strncmp(p->line + p->j, "C ", 2) == 0 && !found[5])
	{
		if (!handle_color(map, p->line + 2, &found[5], 2))
			return (0);
	}
	else if (!is_empty(p->line) && !all_found(found))
		return (0);
	return (1);
}

int	prep_line(t_variables *p)
{
	p->line = get_next_line(p->fd);
	if (!p->line)
		return (1);
	p->j = 0;
	while (p->line[p->j] == ' ' || p->line[p->j] == '\t')
		p->j++;
	if (p->line[p->j] == '\0')
	{
		free(p->line);
		p->i++;
		return (2);
	}
	return (0);
}

void	read_until_eof(t_variables *p, t_map *map)
{
	free(p->line);
	while (1)
	{
		p->line = get_next_line(p->fd);
		if (!p->line)
			break ;
		if (!is_empty(p->line))
		{
			free(p->line);
			break ;
		}
		p->i++;
		free(p->line);
	}
	map->map_start = p->i;
}

int	prep_file(t_variables *p, t_map *map, char *filename)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		p->found[i] = 0;
		i++;
	}
	p->i = 0;
	p->error = 0;
	p->fd = open(filename, O_RDONLY);
	if (p->fd < 0)
		return (1);
	map->texs = malloc(sizeof (char *) * 5);
	if (!map->texs)
		return (-1);
	while (p->i < 5)
		map->texs[p->i++] = NULL;
	p->i = 0;
	return (0);
}

int	parse_info(t_variables *p, t_map *map)
{
	if (!handle_colors_and_textures(p, p->found, map))
		return (close(p->fd), free(p->line), -1);
	else if (map->parser.error)
		return (close(p->fd), free(p->line), -1);
	else if (all_found(p->found) && !p->error)
	{
		read_until_eof(p, map);
		return (close(p->fd), 0);
	}
	return (1);
}
