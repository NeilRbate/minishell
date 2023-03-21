/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_gestion2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:06:12 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/21 07:30:05 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_sig_handle_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		*g_data.status_code = 1;
		exit(0);
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

char	*ft_readpipe(int src, char *line)
{
	char	*stock;

	line = NULL;
	while (1)
	{
		stock = get_next_line(src);
		if (!stock)
			break ;
		if (line)
			line = ft_gstrjoin(stock, line);
		else
			line = ft_strjoin("", stock);
	}
	return (line);
}

char	*ft_herestr(char *line, int fd, t_id *id)
{
	int		t_fd[2];

	pipe(t_fd);
	while (1)
	{
		line = readline(">");
		if (line == NULL || ft_strncmp(line, id->data,
				ft_strlen(line) + 1) == 0)
			break ;
		line = ft_heredocdoll(line);
		ft_putendl_fd(line, t_fd[1]);
		free(line);
	}
	close(t_fd[1]);
	line = ft_readpipe(t_fd[0], line);
	ft_putstr_fd(line, fd);
	close(t_fd[0]);
	return (line);
}

int	ft_heredocstr(t_id *id)
{
	int		fd[2];
	char	*line;
	pid_t	tid;

	pipe(fd);
	line = NULL;
	if (fd < 0)
		return (ft_puterror_fd("pipe fail", 2), -1);
	tid = fork();
	if (tid == 0)
	{
		ft_set_signals_heredoc();
		close(fd[0]);
		line = ft_herestr(line, fd[1], id);
		if (line)
			free(line);
		exit(0);
	}
	else
		waitpid(tid, NULL, 0);
	signal(SIGINT, ft_sig_handle);
	signal(SIGQUIT, ft_sig_handle);
	return (close(fd[1]), fd[0]);
}
