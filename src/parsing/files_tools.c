/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:35:23 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/02 11:07:41 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

char	*ft_gstrjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (s1 == 0 || s2 == 0)
		return (0);
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (ret == 0)
		return (0);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (free(s1), ret);
}

int	ft_writepipe(t_id *id, char	*str)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (free(str), 1);
	write(fd[1], str, ft_strlen(str) + 1);
	close(fd[1]);
	id->infile = fd[0];
	free(str);
	return (0);
}
