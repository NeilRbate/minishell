/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 10:47:47 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/22 08:16:06 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	*ft_retd(int i, int j, char *str)
{
	char	*ret;
	char	*stock;
	char	*doll;

	ret = NULL;
	doll = NULL;
	if (str[i] == '?')
		i++;
	else
	{
		while (str[i] && ft_isalnum(str[i]) == 1)
			i++;
	}
	stock = ft_strndup(str + j, (i - j));
	doll = ft_strdup(stock);
	ret = ft_cutheredocdoll(stock);
	if ((size_t)(i - j) != ft_strlen(str))
		ret = ft_splitdoll(str, doll, ret);
	else
		free(doll);
	return (ret);
}

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
	ret = malloc(sizeof(char) * (i + 100));
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

char	*ft_splitdoll(char *str, char *doll, char *doll_i)
{
	char	**split;
	char	*ret;
	char	*stock;
	int		i;

	i = 0;
	split = ft_splitstr(str, doll);
	if (!split)
		return (NULL);
	if (str[0] == '$' && split[0] != NULL)
		ret = ft_strjoin(doll_i, split[0]);
	else
	{
		ret = ft_strjoin(split[0], doll_i);
		if (split[1] != NULL)
		{
			stock = ret;
			ret = ft_strjoin(stock, split[1]);
			free(stock);
		}
	}
	free(doll_i);
	ft_freesplit(split);
	return (ret);
}
