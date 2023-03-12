/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:12:25 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/12 16:27:24 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/ms.h"

t_id	*ft_heredoc(t_id *id, t_id *s)
{
	char	*line;
	int		fd[2];

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
	pipe(fd);
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
	id->type = 20;
	if (line)
		free(line);
	close(fd[1]);
	if (s != NULL)
		return (s->infile = fd[0], id);
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
