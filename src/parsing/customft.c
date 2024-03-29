/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:43:21 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/30 12:59:37 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	ft_containchar(t_id *id)
{
	int	i;

	i = 0;
	while (id->next != NULL)
	{
		if (id->type == 0)
			i++;
		id = id->next;
	}
	if (id->type == 0)
		i++;
	return (i);
}

char	*ft_strndup(char *str, int size)
{
	char	*ret;

	if (ft_strlen(str) < (size_t)size)
		return (NULL);
	ret = malloc(sizeof(char) * (size + 10));
	ft_memmove(ret, str, size);
	ret[size] = '\0';
	return (ret);
}

int	ft_returnempty(t_id *id)
{
	char	*stock;

	stock = ft_strdup("");
	id = id->next;
	free(id->data);
	id->data = stock;
	if ((id->prev->prev && id->prev->prev->type == 0)
		&& (id->next && id->next->type == 0))
	{
		free(id->data);
		id->data = ft_strjoin(id->prev->prev->data, id->next->data);
		id->prev->prev->type = 20;
		id->next->type = 20;
		id->type = 0;
		return (id->index);
	}
	if ((id->prev->prev && id->prev->prev->type == 0)
		|| (id->next && id->next->type == 0))
		id->type = 20;
	else
		id->type = 0;
	return (id->index);
}

t_id	*ft_joindoll(t_id *id)
{
	char	*stock;

	if (id->next->type != 0)
		return (id->next);
	stock = id->data;
	id->data = ft_strjoin(stock, id->next->data);
	id->type = 0;
	id->next->type = 20;
	free(stock);
	return (id->next);
}
