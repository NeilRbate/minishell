/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:43:21 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/06 10:01:25 by jbarbate         ###   ########.fr       */
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
		printf("str->%s\nsize->%d\n", str, size);
		ret = malloc(sizeof(char) * (size + 1));
		ft_memcpy(ret, str, size);
		printf("ret->%s\n", ret);
		return (ret);
}
