/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idlist_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:12:41 by jbarbate          #+#    #+#             */
/*   Updated: 2023/02/28 13:59:35 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	ft_pipectrl(t_id *id)
{
	while (id->next != NULL)
	{
		if (id->type == 3)
		{
			id = id->next;
			while (id->next != NULL && id->type != 0)
			{
				if (id->type == 3)
					return (ft_putendl_fd("error: invalid syntax", 2), -1);
				id = id->next;
			}
			if (id->type != 0 && id->next == NULL)
				return (ft_putendl_fd("error: invalid syntax", 2), -1);
		}
		else
			id = id->next;
	}
	if ((id->type >= 0 && id->type <= 2)
		|| (id->type >= 5 && id->type <= 6) || id->type >= 10)
		return (0);
	return (ft_putendl_fd("error: invalid syntax", 2), -1);
}

void	ft_catid(t_id *id, int type)
{
	t_id	*stock;
	char	*temp;
	char	*ret;

	stock = id;
	temp = id->data;
	id = id->next;
	while (id->type != type)
	{
		if (id->type == 0)
		{
			ret = temp;
			temp = ft_strjoin(ret, id->data);
			id = id->next;
			free(ret);
			ft_del_idelem(id->prev);
		}
		else
			id = id->next;
	}
	stock->data = temp;
}

int	ft_quotectrl(t_id *id, int type)
{
	t_id	*stock;

	if (id->next == NULL)
		return (ft_putendl_fd("error: invalid syntax 1", 2), -1);
	if (id->next->type == type)
		return (id->next->index);
	id = id->next;
	stock = id;
	while (id->next != NULL)
	{
		if (id->type == 11 && type == 2 && id->next->type == 0)
		{
			id = id->next;
			ft_doll(id);
		}
		else if (id->type != type)
		{
			id->type = 0;
			id = id->next;
		}
		if (id->type == type)
		{
			ft_catid(stock, type);
			if (id->next != NULL)
				return (id->next->index);
			return (id->index);
		}
	}
	return (id->index);
}

int	ft_idctrl(t_id *id)
{
	int	i;

	i = 0;
	while (id != NULL)
	{
		if (id->type == 3 && id->next != NULL && id->next->type == 3)
			return (ft_putendl_fd("error: invalid syntax 4", 2), -1);
		if (id->type == 3 && id->next == NULL)
			return (ft_putendl_fd("error: invalid syntax 5", 2), -1);
		if (id->type == 1 || id->type == 2)
		{
			i = ft_quotectrl(id, id->type);
			if (i < 0)
				return (-1);
			while (i != id->index && id->next != NULL)
				id = id->next;
			if (id->next == NULL)
				return (0);
		}
		else if (id->type == 11)
		{
			id = id->next;
			if (id->type == 0)
			{
				ft_doll(id);
				ft_del_idelem(id->prev);
			}
			else
				id->prev->type = 0;
			i++;
		}
		else
			id = id->next;
	}
	return (0);
}

int	ft_syntax_analyse(t_id *lex)
{
	if (lex->type == 3 || lex->type == 11)
		return (ft_putendl_fd("error: invalid syntax 11", 2), -1);
	if (lex->type == 5 || lex->type == 6)
		while ((lex->type == 5 || lex->type == 6) && lex->next != NULL)
			lex = lex->next;
	if (lex->next == NULL && (lex->type == 5 || lex->type == 6))
		return (ft_putendl_fd("error: invalid syntax 10", 2), -1);
	if (lex->type == 3)
		return (ft_putendl_fd("error: invalid syntax 3", 2), -1);
	if (ft_idctrl(lex) != 0)
		return (-1);
	if (ft_pipectrl(lex) != 0)
		return (-1);
	if (ft_redirctrl(lex) != 0)
		return (-1);
	return (0);
}
