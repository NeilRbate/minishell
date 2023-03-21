/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportquote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:25:47 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/21 15:57:32 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	ft_exportquote(t_id *id)
{
	while (id)
	{
		if (ft_strncmp(id->data, "export", 7) == 0)
		{
			while (id != NULL)
			{
				if (id != NULL
					&& ft_strnstr(id->data, "=", ft_strlen(id->data)) == NULL)
					id = id->next;
				if (id == NULL)
					return ;
				if (id->next)
					id = id->next;
				while (id->next && id->type != 0)
					id = id->next;
				if (id->prev && (id->prev->type == 2 || id->prev->type == 1))
					id->prev->type = 0;
				if (id->next && (id->next->type == 2 || id->next->type == 1))
					id->next->type = 0;
				id = id->next;
			}
			return ;
		}
		id = id->next;
	}
}
