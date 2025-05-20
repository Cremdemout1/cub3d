/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:16:17 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/20 18:45:37 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	handle_texture(t_map *map, char *texture, int *found, int dir)
{
	int	len;

	len = ft_strlen(texture);
	if (texture[len - 1] == '\n')
		texture[len - 1] = '\0';
	if (dir == 1)
		map->texs[0] = ft_strdup(texture + 3);
	else if (dir == 2)
		map->texs[1] = ft_strdup(texture + 3);
	else if (dir == 3)
		map->texs[2] = ft_strdup(texture + 3);
	else if (dir == 4)
		map->texs[3] = ft_strdup(texture + 3);
	*found = 1;
}

int	check_valid_color(t_variables *p)
{
	p->j = 0;
	while (p->split[p->i][p->j] == ' ')
		p->j++;
	if (p->split[p->i][p->j] == '\n' || p->split[p->i][p->j] == '\0')
		return (0);
	p->rgb[p->i] = ft_atoi(p->split[p->i] + p->j);
	if (p->rgb[p->i] > 255 || p->rgb[p->i] < 0
		|| has_non_num_val(p->split[p->i]))
		return (0);
	return (1);
}

int	handle_color(t_map *map, char *color, int *found, int type)
{
	t_variables	p;

	p.i = 0;
	p.split = ft_split(color, ',');
	if (!p.split)
		return (ft_printf_fd(2, "Error\n"), 0);
	if (count_strings(p.split) != 3)
		return (free_array(p.split), 0);
	p.rgb = malloc(sizeof (int) * 3);
	while (p.split[p.i])
	{
		p.len = check_valid_color(&p);
		if (!p.len)
			return (free(p.rgb), free_array(p.split), 0);
		p.i++;
	}
	free_array(p.split);
	if (type == 1)
		map->floor_color = p.rgb;
	else
		map->ceiling_color = p.rgb;
	return (*found = 1, 1);
}

int	get_starting_info(t_map *map, char *filename)
{
	t_variables	p;

	p.x = prep_file(&p, map, filename);
	if (p.x == 1)
		return (perror("Error\nOpening file\n"), 1);
	else if (p.x == -1)
		return (-1);
	while (1)
	{
		p.j = prep_line(&p);
		if (p.j == 1)
			break ;
		else if (p.j == 2)
			continue ;
		p.j = parse_info(&p, map);
		if (p.j <= 0)
			return (p.j);
		free(p.line);
		p.i++;
	}
	map->map_start = p.i;
	if (p.i == 0)
		return (-1);
	return (close(p.fd), -1);
}

char	**get_map(t_map *map, char *filename)
{
	t_variables	p;

	p.i = 0;
	p.fd = open(filename, O_RDONLY);
	if (p.fd < 0)
		return (NULL);
	skip_initial_lines(map, p.fd);
	p.buf = malloc(sizeof(char *) * (map->length + 1));
	if (!p.buf)
		return (NULL);
	while (p.i < map->length)
	{
		p.line = get_next_line(p.fd);
		if (!p.line)
			break ;
		p.len = ft_strlen(p.line);
		if (p.len > 0 && p.line[p.len - 1] == '\n')
			p.line[p.len - 1] = '\0';
		format_line(&p, map->max_width);
	}
	p.buf[p.i] = NULL;
	close (p.fd);
	return (p.buf);
}
