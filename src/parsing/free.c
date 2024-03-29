/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:12:33 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/22 12:20:48 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

t_id	*ft_freeempty(t_id *id)
{
	id->prev->data = ft_gstrjoin(id->prev->data, id->next->data);
	id = id->prev;
	ft_del_idelem(id->next->next);
	ft_del_idelem(id->next);
	return (id);
}

void	ft_del_idlist(t_id *list)
{
	t_id	*stock;

	while (list != NULL)
	{
		stock = list->next;
		if (list->data != NULL)
			free(list->data);
		free(list);
		list = stock;
	}
}

void	ft_del_cmdlist(t_cmd *list)
{
	t_cmd	*stock;

	while (list != NULL)
	{
		stock = list->next;
		if (list->cmd != NULL)
			ft_freesplit(list->cmd);
		free(list);
		list = stock;
	}
	list = 0;
}

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}

void	ft_cleanidws(t_id *id)
{
	t_id	*stock;

	id->prev = NULL;
	while (id->next != NULL)
	{
		if (id->index != 0 && (id->type == 5 || id->type == 20))
		{
			if (id->next == NULL)
				break ;
			else
			{
				stock = id;
				id = id->next;
				id->prev = NULL;
				ft_del_idelem(stock);
			}
		}
		else
			id = id->next;
	}
}
