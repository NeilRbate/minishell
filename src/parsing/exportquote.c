/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportquote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:25:47 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/31 15:16:49 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	ft_cleandoll(t_id *id)
{
	while (id && id->next != NULL)
	{
		if (id && id->type == 20)
		{
			id = id->next;
			ft_del_idelem(id->prev);
		}
		else
			id = id->next;
	}
}

void	ft_exportquote3(t_id *id, t_id *stock)
{
	if (id->prev && (id->prev->type == 2 || id->prev->type == 1))
	{
		if (id->next && (id->next->type == 2 || id->next->type == 1))
		{
			stock->data = ft_strjoin(stock->data, id->data);
			id->type = 20;
			stock = NULL;
		}
	}
}

void	ft_exportquote2(t_id *id, t_id *stock)
{
	while (id != NULL)
	{
		if (id != NULL
			&& ft_strnstr(id->data, "=", ft_strlen(id->data)) == NULL)
			id = id->next;
		if (id == NULL)
			return ;
		if (id->type == 0)
			stock = id;
		else
			return ;
		if (id->next)
			id = id->next;
		if (id->type == 5)
			return ;
		while (id->next && id->type != 0)
			id = id->next;
		ft_exportquote3(id, stock);
		id = id->next;
	}
}

void	ft_exportquote(t_id *id)
{
	t_id	*stock;

	stock = NULL;
	ft_cleandoll(id);
	while (id)
	{
		if (ft_strncmp(id->data, "export", 7) == 0)
		{
			if (id->next)
				id = id->next;
			ft_exportquote2(id, stock);
			return ;
		}
		id = id->next;
	}
}

void	ft_quotedoll(t_id *id)
{
	char	*stock;

	stock = id->next->data;
	id->next->data = ft_strjoin(id->data, id->next->data);
	free(stock);
	id->next->data = ft_heredocdoll(id->next->data);
	id->type = 20;
}
