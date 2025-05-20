/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:26:09 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/20 18:45:52 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	skip_initial_lines(t_map *map, int fd)
{
	int		i;
	char	*line;

	i = 0;
	while (i < map->map_start)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		i++;
	}
}

void	format_line(t_variables *p, int max_width)
{
	p->buf[p->i] = malloc(max_width + 1);
	if (!p->buf[p->i])
		return ;
	p->j = 0;
	while (p->line[p->j] && p->j < max_width)
	{
		if (p->line[p->j] == ' ')
			p->buf[p->i][p->j] = '1';
		else
			p->buf[p->i][p->j] = p->line[p->j];
		p->j++;
	}
	while (p->j < max_width)
	{
		p->buf[p->i][p->j] = '1';
		p->j++;
	}
	p->buf[p->i][p->j] = '\0';
	free(p->line);
	p->i++;
}
