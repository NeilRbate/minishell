/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:19:57 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/08 15:55:55 by jbarbate         ###   ########.fr       */
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
				return (ft_puterror_fd("syntax error", 2), NULL);
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
		if (id->type == 7 || id->type == 8)
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
			return (ft_puterror_fd("syntax error", 2), -1);
	}
	fd = ft_lastredir(id, type);
	return (fd);
}

t_id	*ft_infile(t_id *id, t_id *s)
{
	if (id->next->type != 9 && id->next->type != 0)
		return (ft_puterror_fd("syntax error", 2), NULL);
	id = id->next;
	if (id->next != NULL && id->type == 0 && id->next->type != 9)
	{
		s->infile = ft_openread(id->data);
		if (s->infile < 0)
			return (ft_endredir(id));
		return (id->type = 20, id);
	}
	else
		id = ft_multiinfile2(id, s);
	return (id);
}

int	ft_redirctrl(t_id *id)
{
	t_id	*stock;
	int		fd;

	fd = 1;
	stock = NULL;
	while (id)
	{
		if (id->type == 3)
			stock = NULL;
		else if (id->type == 0)
			stock = id;
		else if (id->type == 10)
			fd = ft_heredoc(id, stock);
		else if (id->type == 9 && stock != NULL)
			id = ft_infile(id, stock);
		else if (id->type == 9)
			id = ft_firstinfile(id);
		else if (id->type == 7 || id->type == 8)
			fd = ft_redir(id);
		if (fd < 0)
			return (0);
		if (id->next == NULL)
			return (0);
		id = id->next;
	}
	return (0);
}
