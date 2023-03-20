/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:13:14 by efirmino          #+#    #+#             */
/*   Updated: 2022/11/14 18:09:37 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	my_wordcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			count++;
		i++;
	}
	return (count);
}

static int	my_create_items(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = 0;
			while (s[j + i] != c && s[j + i] != '\0')
				j++;
			split[k] = malloc(sizeof(char) * (j + 1));
			if (!split[k])
				return (0);
			ft_strlcpy(split[k++], s + i, j + 1);
			i += j;
		}
	}
	split[k] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (0);
	split = malloc(sizeof(char *) * (my_wordcount(s, c) + 1));
	if (!split)
		return (0);
	if (!(my_create_items(split, s, c)))
		return (0);
	return (split);
}
