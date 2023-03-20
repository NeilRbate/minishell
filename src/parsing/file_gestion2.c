/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_gestion2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:06:12 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/20 16:02:39 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_sig_handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_data.heredoc = 1;
		*g_data.status_code = 1;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		return ;
	}
}

void	ft_set_signals_heredoc(void)
{
	signal(SIGINT, ft_sig_handle_heredoc);
	signal(SIGQUIT, ft_sig_handle_heredoc);
}

int	ft_heredocstr(t_id *id)
{
	int		fd[2];
	char	*line;
	pid_t	tid;

	pipe(fd);
	if (fd < 0)
		return (ft_puterror_fd("pipe fail", 2), -1);
	tid = fork();
	if (tid == 0)
	{
		while (1)
		{
			line = readline(">");
			if (line == NULL || ft_strncmp(line, id->data,
					ft_strlen(line) + 1) == 0)
				exit(0);
			line = ft_heredocdoll(line);
			ft_putendl_fd(line, fd[1]);
			free(line);
		}
		if (line)
			free(line);
		exit(0);
	}
	else
		close(fd[1]);
	return (fd[0]);
}
