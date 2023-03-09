/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:43:21 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/09 08:46:47 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_cut(char *str, int i, char *charset)
{
	char	*ret;
	int		j;
	int		k;

	j = 0;
	ret = NULL;
	k = i;
	while (str[k] != '\0' && is_charset(str[k], charset) == 0)
	{
		j++;
		k++;
	}
	ret = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (i < k)
	{
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	**ft_splitstr(char *str, char *charset)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	j = 0;
	ret = NULL;
	while (str[i])
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i])
	{
		if (is_charset(str[i], charset) == 0)
		{
			ret[j] = ft_cut(str, i, charset);
			j++;
			while (is_charset(str[i], charset) == 0 && str[i])
				i++;
		}
		else
			i++;
	}
	ret[j] = NULL;
	return (ret);
}

int	ft_containchar(t_id *id)
{
	int	i;

	i = 0;
	while (id->next != NULL)
	{
		if (id->type == 0)
			i++;
		id = id->next;
	}
	if (id->type == 0)
		i++;
	return (i);
}

char	*ft_strndup(char *str, int size)
{
	char	*ret;

	if (ft_strlen(str) < (size_t)size)
		return (NULL);
	ret = malloc(sizeof(char) * (size + 1));
	ft_memcpy(ret, str, size);
	return (ret);
}
