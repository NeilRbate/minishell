/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 09:20:11 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/09 11:56:08 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_id	*ft_multioutfile2(t_id *id, t_id *stock)
{
	int	fd;
	int	type;

	type = id->type;
	while (id->next != NULL && id->type != 3)
	{
		if(id->type >= 7 && id->type <= 8 && id->next != NULL && id->next->type != 0)
			return (ft_puterror_fd("syntax error", 2), NULL);
		if (id->next->type == 0 && id->type >= 7 && id->type <= 8)
		{
			fd = ft_openredir(id->data, type);
			if (id < 0)
				return (stock->type = 20, ft_endredir(id));
			close (fd);
			type = id->type;
			id->type = 20;
		}
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
	if (id->next->type != 0)
		return (ft_puterror_fd("invalid syntax", 2), NULL);
	id = id->next;
	if (id->type == 0 && (id->next == NULL || id->next->type == 3 ||
			id->next->type != 7 || id->next->type != 8))
	{
		stock->outfile = ft_openredir(id->data, type);
		if (stock->outfile < 0)
			return (ft_endredir(id));
		if (stock->prev != NULL && stock->prev->type == 0)
			stock->prev->outfile = stock->outfile;
		return (id->type = 20, id);
	}
	else
		id = ft_multioutfile2(id, stock);
	return (id);
}
