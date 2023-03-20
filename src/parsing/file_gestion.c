/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:12:25 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/20 14:06:29 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

t_id	*ft_heredoc(t_id *id, t_id *s)
{
	int		fd;

	ft_set_signals_heredoc();
	if (s == NULL)
	{
		if (id->next != NULL)
			id = id->next;
		if (id->next != NULL)
			s = id->next;
		else
			s = NULL;
	}
	else
		id = id->next;
	fd = ft_heredocstr(id);
	signal(SIGINT, ft_sig_handle);
	signal(SIGQUIT, ft_sig_handle);
	if (fd < 0)
		return (NULL);
	id->type = 20;
	if (s != NULL)
		return (s->infile = fd, id);
	return (id);
}

int	ft_openread(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_putendl_fd("minishell: stdin: Is a directory", 2);
		*g_data.status_code = 1;
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		*g_data.status_code = 1;
		return (-1);
	}
	return (fd);
}

int	ft_openwrited(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Is a directory", 2);
		*g_data.status_code = 1;
		return (-1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		return (-1);
	}
	return (fd);
}

int	ft_openwrite(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": Is a directory", 2);
		*g_data.status_code = 1;
		return (-1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		return (-1);
	}
	return (fd);
}

int	ft_openredir(char *file, int type)
{
	if (type == 8)
		return (ft_openwrited(file));
	else if (type == 7)
		return (ft_openwrite(file));
	return (-1);
}
