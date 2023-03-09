/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:19:57 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/09 11:56:41 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_id	*ft_multioutfile(t_id *id, int type)
{
	int	fd;

	while (id->next != NULL && id->type != 3)
	{
		if (id->type == 0 && id->next->type >= 7 && id->next->type <= 8)
		{
			id->type = 20;
			fd = ft_openredir(id->data, type);
			if (id < 0)
				return (ft_endredir(id));
			type = id->next->type;
			close (fd);
		}
		else if (id->type == 0 && id->next->type == 0)
		{
			id->type = 20;
			id->next->outfile = ft_openredir(id->data, type);
			if (id->next->outfile < 0)
				return (ft_endredir(id));
			return (id);
		}
		id = id->next;
	}
	return (id);
}

t_id	*ft_firstoutfile(t_id *id, int type)
{
	t_id	*stock;

	stock = id;
	id = id->next;
	if (id->type == 0 && id->next != NULL && id->next->type == 0)
	{
		id->next->outfile = ft_openredir(id->data, type); 
		if (id->next->infile > 0)
			return (ft_endredir(id));
		id->type = 20;
		stock->type = 20;
	}
	else
		return (ft_multioutfile(id, type));
	return (id);
}

t_id	*ft_redir(t_id *id, t_id *stock)
{
	if (stock == NULL)
		return (ft_firstoutfile(id, id->type));
	else
		return (ft_lastoutfile(id, stock));
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
			id = ft_heredoc(id, stock);
		else if (id->type == 9 && stock != NULL)
			id = ft_infile(id, stock);
		else if (id->type == 9)
			id = ft_firstinfile(id);
		else if (id->type == 7 || id->type == 8)
			id = ft_redir(id, stock);
		if (fd < 0)
			return (0);
		if (id->next == NULL)
			return (0);
		id = id->next;
	}
	return (0);
}
