/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:41:31 by yohan             #+#    #+#             */
/*   Updated: 2024/12/04 16:32:09 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	len;

	j = 0;
	len = 0;
	while (src[len])
		len++;
	if (size == 0)
		return (len);
	while (src[j] && j < (size - 1))
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (len);
}

char *ft_strncpy(char *dest, char *src, unsigned int n)
{
    unsigned int i;

    i = 0;

    while(src[i] != '\0' && i < n)
    {
        dest[i] = src[i];
        i++;
    }
    while((unsigned int)dest[i] < n)
    {
		dest[i] = '\0';
		i++;
    }
    
    return 0;
}
/*
int	main (void)
{
	char	x[20];
	char	y[10];

	y[10] = "hello";
	printf("%zu", ft_strlcpy(x, y, 20));
	return (0);
}
 */