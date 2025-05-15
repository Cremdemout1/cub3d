/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   flood.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ycantin <ycantin@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/28 20:52:34 by ycantin		   #+#	#+#			 */
/*   Updated: 2025/05/07 18:35:38 by ycantin		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/main.h"

void	initialize_visit_state(t_map *map)
{
	t_variables	p;

	if (!init_initial_state(&p, map->length))
		return ;
	while (p.y < map->length)
	{
		p.visited[p.y] = malloc (sizeof(bool) * map->width[p.y]);
		if (!p.visited[p.y])
			return ;
		p.x = 0;
		while (p.x < map->width[p.y])
		{
			if (map->map[p.y][p.x] == '0' || map->map[p.y][p.x] == 'N'
				|| map->map[p.y][p.x] == 'S' || map->map[p.y][p.x] == 'W'
					|| map->map[p.y][p.x] == 'E')
				p.visited[p.y][p.x] = false;
			else if (map->map[p.y][p.x] == '1')
				p.visited[p.y][p.x] = true;
			else
				p.visited[p.y][p.x] = false;
			p.x++;
		}
		p.y++;
	}
	map->parser.visited = p.visited;
}

char	**buffed_map(t_map *map)
{
	t_variables	p;

	p._map = malloc (sizeof (char *) * (map->length + 2 + 1));
	p.i = 1;
	p.j = 0;
	p._map[0] = malloc(sizeof (char) * (map->max_width + 2 + 1));
	while (p.j < map->max_width + 1)
		p._map[0][p.j++] = 'o';
	p._map[0][p.j] = '\0';
	buffed_map_inner_loop(&p, map);
	p.j = 0;
	p._map[p.i] = malloc(sizeof (char) * (map->max_width + 2 + 1));
	while (p.j < map->max_width + 1)
		p._map[p.i][p.j++] = 'o';
	p._map[p.i][map->max_width + 1] = '\0';
	p._map[p.i + 1] = NULL;
	return (p._map);
}

void	reverse_fill(char **map, int x, int y, t_map *map_info)
{
	if (x < 0 || x > (map_info->max_width + 1)
		|| y < 0 || y > (map_info->length + 1))
		return ;
	if (map[y][x] == 'v' || map[y][x] == '1'
		|| map_info->parser.error == 1)
		return ;
	if (map[y][x] == '0')
	{
		printf("%d  %d\n", x, y);
		map_info->parser.error = 1;
		return ;
	}
	map[y][x] = 'v';
	reverse_fill(map, x + 1, y, map_info);
	reverse_fill(map, x - 1, y, map_info);
	reverse_fill(map, x, y + 1, map_info);
	reverse_fill(map, x, y - 1, map_info);
}

void	fill(t_fill_context *ctx, int x, int y)
{
	if (*(ctx->error))
		return ;
	if (ctx->visited[y][x])
		return ;
	if (ctx->map[y][x] != '1' && ctx->map[y][x]
		!= '0' && ctx->map[y][x] != ctx->player)
	{
		*ctx->error = true;
		return ;
	}
	ctx->visited[y][x] = true;
	fill(ctx, x + 1, y);
	fill(ctx, x - 1, y);
	fill(ctx, x, y + 1);
	fill(ctx, x, y - 1);
}

// void	fill(char **map, int x, int y, 
// bool *error, bool ***visited, char player)
// {
//	 if (*error == 1)
//		 return ;
//	 if ((*visited)[y][x] == true)
//		 return ;
//	 if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != player)
//	 {
//		 *error = true;
//		 return ;
//	 }
//	 (*visited)[y][x] = true;
//	 fill(map, x + 1, y, error, visited, player);
//	 fill(map, x - 1, y, error, visited, player);
//	 fill(map, x, y + 1, error, visited, player);
//	 fill(map, x, y - 1, error, visited, player);
// }

void	flood_fill(t_map *map)
{
	char	**buf_map;

	buf_map = buffed_map(map);
	if (!buf_map)
	{
		ft_printf_fd(2, "Error\n buffer map allocation error\n");
		map->parser.error = 1;
		return ;
	}
	reverse_fill(buf_map, 0, 0, map);
	free_array(buf_map);
	if (map->parser.error == 1)
	{
		ft_printf_fd(2, "Error\nPlayer not surrounded by walls\n");
		return ;
	}
	initialize_visit_state(map);
	fill(&(t_fill_context){.map = map->map,
		.visited = map->parser.visited, .error = &map->parser.error,
		.player = map->dir}, map->x_player, map->y_player);
	if (map->parser.error == 1)
	{
		ft_printf_fd(2, "Error\nPlayer not surrounded by walls\n");
		return ;
	}
}
