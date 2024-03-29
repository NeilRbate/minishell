/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idlist_ctrl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:12:41 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/31 16:28:20 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

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
					return (ft_putperror_fd(), -1);
				id = id->next;
			}
			if (id->type != 0 && id->next == NULL)
				return (ft_putserror_fd(), -1);
		}
		else
			id = id->next;
	}
	if ((id->type >= 0 && id->type <= 2)
		|| (id->type >= 5 && id->type <= 6) || id->type >= 10)
		return (0);
	return (ft_putnlerror_fd(), -1);
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
		return (ft_putserror_fd(), -1);
	if (id->next->type == type)
		return (ft_returnempty(id));
	stock = id->next;
	while (id->next != NULL)
	{
		id = id->next;
		if (stock->type != 0)
			stock = id;
		if (id->type == 11 && type == 2 && id->next->type == 0)
			ft_quotedoll(id);
		else if (id->type != type)
			id->type = 0;
		if (id->type == type)
		{
			ft_catid(stock, type);
			if (id->next != NULL)
				return (id->next->index);
			return (id->index);
		}
	}
	return (ft_putserror_fd(), -1);
}

int	ft_idctrl(t_id *id, int i)
{
	while (id != NULL)
	{
		if (id->type == 4)
			return (ft_putserror_fd(), -1);
		if (id->type == 3 && id->next != NULL && id->next->type == 3)
			return (ft_putpperror_fd(), -1);
		if (id->type == 3 && id->next == NULL)
			return (ft_putperror_fd(), -1);
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
		else if (id->type == 11 && id->next != NULL)
			id = ft_dollctrl(id, &i);
		id = id->next;
	}
	return (0);
}

int	ft_syntax_analyse(t_id *lex)
{
	if (lex->type == 3 && lex->next && lex->next->type == 3)
		return (ft_putpperror_fd(), -1);
	if (lex->type == 3)
		return (ft_putperror_fd(), -1);
	if (lex->type == 5 || lex->type == 6)
		while ((lex->type == 5 || lex->type == 6) && lex->next != NULL)
			lex = lex->next;
	if (lex->next == NULL && (lex->type == 5 || lex->type == 6))
		return (-1);
	if (lex->type == 3 && lex->next && lex->next->type == 3)
		return (ft_putpperror_fd(), -1);
	if (lex->type == 3)
		return (ft_putperror_fd(), -1);
	if (ft_idctrl(lex, 0) != 0)
		return (-1);
	if (ft_pipectrl(lex) != 0)
		return (-1);
	if (ft_stxctrl(lex) != 0)
		return (-1);
	ft_exportquote(lex);
	ft_cleanidws(lex);
	if (ft_redirctrl(lex, lex) != 0)
		return (-1);
	return (0);
}
