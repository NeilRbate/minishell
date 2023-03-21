/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:16:07 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/21 15:43:36 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_cmd	*ft_ret(t_cmd *ret, int i, t_id *id, t_id *stock)
{
	char	**cmd;
	int		j;

	j = 0;
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (ft_puterror_fd("malloc fail", 2), NULL);
	cmd[i] = NULL;
	while (j < i)
	{
		if (stock->type != 3)
			cmd[j] = ft_strdup(stock->data);
		if (stock->next != NULL)
			stock = stock->next;
		else
			break ;
		j++;
	}
	if (ret == NULL)
		ret = ft_create_cmdlist(cmd, 0, id->infile, id->outfile);
	else
		ft_add_cmdelem(ret, cmd, id->infile, id->outfile);
	return (ret);
}

t_cmd	*ft_cmdlist(t_id *id)
{
	t_cmd	*ret;
	t_id	*stock;
	int		i;

	ret = NULL;
	while (id != NULL)
	{
		i = 1;
		stock = id;
		while (id->next != NULL && id->type != 3)
		{
			id = id->next;
			id->infile = id->prev->infile;
			id->outfile = id->prev->outfile;
			if (id->type != 3)
				i++;
		}
		ret = ft_ret(ret, i, id, stock);
		if (id->next == NULL)
			return (ret);
		if (id->type == 3)
			id = id->next;
	}
	return (ret);
}

t_id	*ft_clean(t_id *id)
{
	if (id->type == 0 || id->type == 3)
		id = id->next;
	else if (id->next != NULL)
	{
		id = id->next;
		ft_del_idelem(id->prev);
	}
	else
	{
		if (id->type != 0)
		{
			id->prev->next = NULL;
			ft_del_idelem(id);
		}
		id = NULL;
	}
	return (id);
}

t_id	*ft_clean_id(t_id *id)
{
	t_id	*stock;

	while (id->type != 0 && id != NULL)
	{
		id = id->next;
		ft_del_idelem(id->prev);
	}
	stock = id;
	if (stock == NULL || stock->next == NULL)
		return (stock);
	while (id != NULL)
		id = ft_clean(id);
	return (stock);
}

t_cmd	*ft_parsing(char *str)
{
	t_id	*lex;
	t_cmd	*cmd;

	if (str[0] == '\0')
		return (ft_puterror_fd("invalid syntax", 2), NULL);
	lex = ft_lexical_analyse(str);
	if (!lex)
		return (NULL);
	if (ft_syntax_analyse(lex) != 0)
		return (ft_del_idlist(lex), NULL);
	if (ft_containchar(lex) == 0)
		return (ft_del_idlist(lex), NULL);
	lex = ft_clean_id(lex);
	cmd = ft_cmdlist(lex);
	if (!cmd)
		return (ft_del_idlist(lex), NULL);
	ft_del_idlist(lex);
	ft_isbuiltin(cmd);
	ft_print_cmdlist(cmd);
	return (cmd);
}
