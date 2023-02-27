/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:12:25 by jbarbate          #+#    #+#             */
/*   Updated: 2023/02/27 11:46:31 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	ft_heredoc(char *limiter)
{
	char	*str;
	char	*line;

	str = malloc(1);
	if (!str)
		return (-1);
	str[0] = '\0';
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strnstr(line, limiter, ft_strlen(limiter))
			&& ft_strlen(limiter) == (ft_strlen(line) - 1))
			break ;
		str = ft_gstrjoin(str, line);
		free(line);
	}
	close(0);
	return (ft_writepipe(str));
}

int	ft_openread(char *file)
{
	int	fd;
	int	empty_fd[2];

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_putendl_fd("error: Try to open a directory", 2);
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(file);
		pipe(empty_fd);
		close(empty_fd[1]);
		return (empty_fd[0]);
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
		ft_putendl_fd("error: Try to open a directory", 2);
		return (-1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
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
		ft_putendl_fd("error: Try to open a directory", 2);
		return (-1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(file);
		return (-1);
	}
	return (fd);
}

int	ft_openredir(char *file, int type, t_id *id)
{
	if (type == 7)
		return (ft_openwrite(file));
	else if (type == 8)
		return (ft_openwrited(file));
	else if (type == 9)
		return (ft_openread(file));
	else if (type == 10)
	{
		while (id->type != 0)
		{
			id = id->next;
			if (id->type != 5 || id->type != 0)
				return (ft_putendl_fd("error: invalid syntax", 2), -1);
			if (id->type == 0)
				return (ft_heredoc(id->data));
		}
		return (-1);
	}
	return (-1);
}
