/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 07:17:39 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/07 10:47:40 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_id	*ft_multiinfile(t_id *id)
{
	int	fd;

	while (id->next != NULL && id->type != 3)
	{
		if (id->type == 0 && id->next->type == 9)
		{
			fd = ft_openread(id->data);
			if (fd < 0)
				return (NULL);
			close(fd);
			id->type = 20;
			id = id->next;
		}
		else if (id->next != NULL && id->type == 0 && id->next->type == 0)
		{
			id->next->infile = ft_openread(id->data);
			if (id->next->infile < 0)
				return (NULL);
			id->type = 20;
			return (id);
		}
		id = id->next;
	}
	return (id);
}

t_id	*ft_firstinfile(t_id *id)
{
	t_id	*stock;

	stock = id;
	id = id->next;
	if (id->type == 0 && id->next != NULL && id->next->type != 9)
	{
		id->next->infile = ft_openread(id->data);
		if (id->next->infile < 0)
			return (NULL);
		id->type = 20;
		stock->type = 20;
	}
	else
		return (ft_multiinfile(id));
	return (id);
}
