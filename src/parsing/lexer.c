/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:16:56 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/13 12:27:17 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	ft_deftype(char c, char d, int *i)
{
	if (c == 39)
		return ((*i += 1), 1);
	else if (c == 34)
		return ((*i += 1), 2);
	else if (c == '|')
		return ((*i += 1), 3);
	else if (c == 92)
		return ((*i += 1), 4);
	else if (c == '\t' || c == 32)
		return ((*i += 1), 5);
	else if (c == '\n')
		return ((*i += 1), 6);
	else if (c == '>' && d == '>')
		return (8);
	else if (c == '>')
		return ((*i += 1), 7);
	else if (c == '<' && d == '<')
		return (10);
	else if (c == '<')
		return ((*i += 1), 9);
	else if (c == '$')
		return ((*i += 1), 11);
	return (0);
}

int	ft_cutredir(int type, t_id *lex, char *str, int k)
{
	char	*s;

	s = malloc(3);
	if (!s)
		return (ft_puterror_fd("malloc fail", 2), -1);
	s[2] = '\0';
	ft_memmove(s, str, 2);
	ft_add_idelem(lex, type, k, s);
	return (2);
}

int	ft_cuttype(int type, t_id *lex, char *str, int k)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = NULL;
	if (type == 0)
	{
		while (str[j] && ft_deftype(str[i], str[i + 1], &i) == 0)
		{
			j++;
			i++;
		}
		i--;
		s = malloc(sizeof(char) * j + 1);
		if (!s)
			return (ft_puterror_fd("malloc fail", 2), -1);
		s[j] = '\0';
		ft_memmove(s, str, j);
	}
	else if (type == 8 || type == 10)
		return (ft_cutredir(type, lex, str, k));
	ft_add_idelem(lex, type, k, s);
	return (j);
}

char	*ft_createstr(char c)
{
	char	*s;

	s = malloc(2);
	if (!s)
		return (ft_puterror_fd("malloc fail", 2), NULL);
	s[0] = c;
	s[1] = '\0';
	return (s);
}

t_id	*ft_lexical_analyse(char *str)
{
	t_id	*lex;
	t_id	*stock;
	int		i;
	int		j;
	int		type;

	i = 0;
	j = 0;
	lex = ft_create_idlist(0, 0, NULL);
	while (str[j])
	{
		type = ft_deftype(str[i], str[i + 1], &i);
		if (type == 0 || type == 8 || type == 10)
			i += ft_cuttype(type, lex, str + i, i);
		else
			ft_add_idelem(lex, type, j, ft_createstr(str[j]));
		j = i;
	}
	stock = lex->next;
	free(lex->data);
	free(lex);
	lex = stock;
	return (lex);
}
