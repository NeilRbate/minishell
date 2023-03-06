/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:43:21 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/06 08:49:51 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	*ft_strndup(char *str, int size)
{
		int		i;
		char	*ret;

		i = 0;
		if (ft_strlen(str) < (size_t)size)
			return (NULL);
		ret = malloc(sizeof(char) * (size + 1));
		while (i < size)
		{
			ret[i] = str[i];
			i++;
		}
		ret[i] = '\0';
		return (ret);
}
