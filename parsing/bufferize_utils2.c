/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bufferize_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:26:09 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/20 18:46:26 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	all_found(int *found)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!found[i])
			return (0);
		i++;
	}
	return (1);
}

bool	has_non_num_val(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!str[i])
			return (false);
		if (!(str[i] >= '0' && str[i] <= '9')
			&& str[i] != ' ' && str[i] != '\n')
			return (true);
		i++;
	}
	return (false);
}

bool	is_valid_file(char *file)
{
	if (access(file, F_OK) == 0)
		return (true);
	return (false);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}
