/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:43:21 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/09 14:43:42 by jbarbate         ###   ########.fr       */
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
	ret = malloc(sizeof(char) * (size + 1));
	ft_memcpy(ret, str, size);
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
