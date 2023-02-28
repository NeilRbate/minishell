/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:19:57 by jbarbate          #+#    #+#             */
/*   Updated: 2023/02/28 14:39:30 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	ft_lastredir(t_id *id, int type)
{
	int		fd;
	t_id	*stock;

	fd = ft_openredir(id->data, type, id);
	if (fd < 0)
		return (ft_putendl_fd("error: fail to open", 2), -1);
	id->type = 20;
	while (id->next != NULL && id->type != 3)
	{
		id = id->next;
		if (id->type == 0)
			stock = id;
		else if (id->type >= 7 && id->type < 10)
		{
			close(fd);
			type = id->type;
			fd = -1;
			while (id->next != NULL && id->type != 0 && id->type != 3)
			{
				id = id->next;
				if (id->type != 5 && id->type != 0)
					return (ft_putendl_fd("error: invalid syntax", 2), -1);
				if (id->type == 0)
				{
					fd = ft_openredir(id->data, type, id);
					id->type = 20;
					if (id->next != NULL)
					{
						id = id->next;
						ft_del_idelem(id->prev);
					}
					break;
				}
			}
		}
	}
	return (fd);
}

int	ft_redir(t_id *id)
{
	int		fd;
	int		type;

	type = id->type;
	while (id->next != NULL && id->type != 0)
	{
		id = id->next;
		if (id->type != 5 && id->type != 0 && (id->type < 7 || id->type > 10))
			return (ft_putendl_fd("error: invalid syntax", 2), -1);
	}
	fd = ft_lastredir(id, type);
	return (fd);
}

int	ft_redirctrl(t_id *id)
{
	t_id	*stock;
	int		fd;
	int		index;

	stock = id;
	index = id->index;
	while (id->type != 0)
		id = id->next;
	while (id->next != NULL)
	{
		id = id->next;
		if (id->type == 0)
			stock = id;
		if (id->type == 10)
		{
			while (id->next != NULL && id->type != 0)
				id = id->next;
			if (id->type != 0)
				return (-1);
			ft_heredoc(id);
		}

		else if (id->type >= 7 && id->type < 10)
		{
			fd = ft_redir(id);
			if (fd < 0)
				return (-1);
			if (id->type == 7 || id->type == 8)
				stock->outfile = fd;
			else if (id->type == 9)
				stock->infile = fd;
		}
	}
	return (0);
}
