/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycantin <ycantin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 12:42:55 by yohan             #+#    #+#             */
/*   Updated: 2025/05/26 15:40:38 by ycantin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_split_wordcount(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return (0);
	while (split[i])
		i++;
	return (i);
}

static int	ft_count_words(const char *str, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	if (!str || !*str)
		return (0);
	while (str[i] == c && str[i])
		i++;
	while (str[i])
	{
		if (str[i] != c)
		{
			word_count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else if (str[i] == c)
			i++;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	t_vars	var;

	if (!s)
		return (NULL);
	var.word_count = ft_count_words((char *)s, c);
	var.i = 0;
	var.start = 0;
	var.str_index = 0;
	var.dest = (char **)malloc((var.word_count + 1) * sizeof(char *));
	if (!var.dest)
		return (NULL);
	while (s[var.i])
	{
		if (s[var.i] == c)
		{
			var.i++;
			continue ;
		}
		var.start = var.i;
		while (s[var.i] && s[var.i] != c)
			var.i++;
		var.dest[var.str_index++] = ft_substr(s, var.start, var.i - var.start);
	}
	var.dest[var.str_index] = NULL;
	return (var.dest);
}

char	**ft_split2(char const *s, char c)
{
	t_vars	var;

	if (!s)
		return (NULL);
	var.i = 0;
	var.str_index = 0;
	var.dest = (char **)malloc((ft_strlen(s) + 2) * sizeof(char *));
	if (!var.dest)
		return (NULL);
	while (1)
	{
		var.start = var.i;
		while (s[var.i] && s[var.i] != c)
			var.i++;
		var.dest[var.str_index++] = ft_substr(s, var.start, var.i - var.start);
		if (!s[var.i])
			break ;
		var.i++;
	}
	var.dest[var.str_index] = NULL;
	return (var.dest);
}

/*
int main (void)
{
	int		i;
	char	**words;

	i = 0;
	words = ft_split ("lorem,ipsum,dolor,sit,amet", ',');
	while (words[i])
	{
		printf("%s\n", words[i]);
		i++;
	}
	free (words);
	return (0);
}
*/