/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:43:21 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/08 15:54:04 by jbarbate         ###   ########.fr       */
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
	printf("str->%s\nsize->%d\n", str, size);
	ret = malloc(sizeof(char) * (size + 1));
	ft_memcpy(ret, str, size);
	printf("ret->%s\n", ret);
	return (ret);
}
