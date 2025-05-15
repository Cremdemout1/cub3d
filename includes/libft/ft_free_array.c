/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:57:16 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/07 15:59:24 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array || !array[i])
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_bool_array(bool **array, int n)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (i < n)
	{
		free(array[i]);
		i++;
	}
	free(array);
}