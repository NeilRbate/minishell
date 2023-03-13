/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_gestion2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:06:12 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/13 12:15:33 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

int	ft_heredocstr(t_id *id)
{
	int		fd[2];
	char	*line;

	pipe(fd);
	if (fd < 0)
		return (ft_puterror_fd("pipe fail", 2), -1);
	while (1)
	{
		line = readline(">");
		if (line == NULL || ft_strncmp(line, id->data,
				ft_strlen(line) + 1) == 0)
			break ;
		line = ft_heredocdoll(line);
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
	if (line)
		free(line);
	close(fd[1]);
	return (fd[0]);
}
