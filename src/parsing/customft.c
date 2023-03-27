/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:43:21 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/27 18:54:08 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	ft_isanequal(t_id *id)
{
	int	i;

	i = 0;
	if (!id)
		return (0);
	while (id && id->data && id->data[i] != '\0')
		i++;
	if (i > 0)
		i--;
	else
		return (0);
	if (id->data[i] == '=')
	{
		id->data = ft_strjoin(id->data, id->next->next->data);
		ft_del_idelem(id->next);
		return (1);
	}
	return (0);
}

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

	stock = malloc(sizeof(char) * 2);
	if (!stock)
		return (ft_puterror_fd("malloc fail", 2), -1);
	stock[0] = 32;
	stock[1] = '\0';
	id->type = 20;
	id = id->next;
	free(id->data);
	id->data = stock;
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
