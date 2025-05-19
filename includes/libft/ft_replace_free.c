/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:19:43 by ycantin           #+#    #+#             */
/*   Updated: 2025/05/19 15:19:45 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	replace_and_free(char **target, char *replacement)
{
	if (*target)
		free(*target);
	*target = replacement;
}

void	free_and_allocate(char **target, char *replacement, bool to_free)
{
	if (*target)
		free(*target);
	if (!replacement)
		*target = NULL;
	else
		*target = ft_strdup(replacement);
	if (to_free && replacement)
		free(replacement);
}
