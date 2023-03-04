/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:19:57 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/04 09:57:21 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_id	*ft_last(t_id *id, int *fd, int *type)
{
	if (id->type >= 7 && id->type < 10)
	{
		close(*fd);
		*type = id->type;
		*fd = -1;
		while (id->next != NULL && id->type != 0 && id->type != 3)
		{
			id = id->next;
			if (id->type != 5 && id->type != 0)
				return (ft_puterror_fd("invalid syntax", 2), NULL);
			if (id->type == 0)
			{
				*fd = ft_openredir(id->data, *type, id);
				id->type = 20;
				if (id->next != NULL)
				{
					id = id->next;
					ft_del_idelem(id->prev);
				}
				break ;
			}
		}
	}
	return (id);
}

int	ft_lastredir(t_id *id, int type)
{
	int		fd;

	fd = ft_openredir(id->data, type, id);
	if (fd < 0)
		return (ft_puterror_fd("fail to open", 2), -1);
	id->type = 20;
	while (id->next != NULL && id->type != 3)
	{	
		id = id->next;
		id = ft_last(id, &fd, &type);
		if (!id)
			return (-1);
	}
	return (fd);
}

int	ft_redir(t_id *id)
{
	int		fd;
	int		type;

	type = id->type;
	id = id->next;
	while (id->next != NULL && id->type != 0)
	{
		if (id->type == 5 || id->type == 0)
			id = id->next;
		else
			return (ft_puterror_fd("invalid syntax", 2), -1);
	}
	fd = ft_lastredir(id, type);
	return (fd);
}

int	ft_infile(t_id *id, t_id *s)
{
	t_id	*stock;
	int		fd;

	stock = id;
	while (id->next != NULL && id->type != 0 && id->type != 3)
	{
		id = id->next;
		if (id->type == 0)
		{
			fd = ft_openread(id->data);
			if (fd < 0)
				return (-1);
			else
			{
				while (stock->index != id->index)
				{
					stock = stock->next;
					ft_del_idelem(stock->prev);
				}
				s->infile = fd;
				return (fd);
			}
		}
	}
	return (ft_puterror_fd("invalid syntax", 2), -1);
}

int	ft_redirctrl(t_id *id)
{
	t_id	*stock;
	t_id	*cmd;
	int		fd;

	stock = id;
	fd = 1;
	while (id->type != 0)
		id = id->next;
	cmd = id;
	while (id->next != NULL)
	{
		id = id->next;
		if (id->type == 0)
			stock = id;
		else if (id->type == 10)
			fd = ft_heredoc(id, stock);
		else if (id->type == 9)
			fd = ft_infile(id, stock);
		else if (id->type == 7 || id->type == 8)
		{
			cmd->outfile = ft_redir(id);
			return (0);
		}
		if (fd < 0)
			return (ft_puterror_fd("invalid fd", 2), -1);
	}
	return (0);
}
