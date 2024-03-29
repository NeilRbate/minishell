/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 09:20:11 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/22 08:51:58 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

t_id	*ft_multioutfile3(t_id *id, t_id *stock, int *type)
{
	int	fd;

	fd = ft_openredir(id->data, *type);
	if (fd < 0)
		return (stock->type = 20, ft_endredir(id));
	close (fd);
	*type = id->type;
	id->type = 20;
	return (id);
}

t_id	*ft_multioutfile2(t_id *id, t_id *stock)
{
	int	type;

	type = id->type;
	while (id->next != NULL && id->type != 3)
	{
		if (id->type >= 7 && id->type <= 8
			&& id->next != NULL && id->next->type != 0)
			return (ft_putnlerror_fd(), id);
		if (id->next->type == 0 && id->type >= 7 && id->type <= 8)
			id = ft_multioutfile3(id, stock, &type);
		else if (id->type == 0 && id->next->type == 0)
		{
			id->type = 20;
			stock->outfile = ft_openredir(id->data, type);
			if (stock->outfile < 0)
				return (ft_endredir(id));
			return (id);
		}
		id = id->next;
	}
	return (id);
}

t_id	*ft_lastoutfile(t_id *id, t_id *stock)
{
	int	type;

	type = id->type;
	if (id->next != NULL && id->next->type != 0)
		return (ft_putnlerror_fd(), stock->type = 20, id);
	id = id->next;
	if (id->type == 0 && (id->next == NULL || id->next->type == 3
			|| id->next->type != 7 || id->next->type != 8))
	{
		stock->outfile = ft_openredir(id->data, type);
		if (stock->outfile < 0)
		{
			if (stock->prev != NULL && stock->prev == 0)
				stock->prev->type = 20;
			return (stock->type = 20, ft_endredir(id));
		}
		if (stock->prev != NULL && stock->prev->type == 0)
			stock->prev->outfile = stock->outfile;
		return (id->type = 20, id);
	}
	else
		return (ft_multioutfile2(id, stock));
	return (id);
}
