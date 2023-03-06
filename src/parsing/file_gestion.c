/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:12:25 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/06 09:19:03 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"
#include "../../include/ms.h"

int	ft_heredoc(t_id *id, t_id *s)
{
	char	*line;
	int		fd[2];

	s = id->prev;
	printf("s->data ->%s\n", s->data);
	pipe(fd);
	while (id->next != NULL && id->type != 0)
		id = id->next;
	if (id->type != 0)
		return (ft_puterror_fd("invalid syntax", 2), -1);
	while (1)
	{
		line = readline(">");
		if ((ft_strnstr(line, id->data, ft_strlen(id->data) + 1)
				|| line == NULL) && line[0] != 0)
			break ;
		//line = ft_heredocdoll(line);
		ft_putstr_fd(line, fd[1]);
		free(line);
	}
	id->type = 20;
	if (line)
		free(line);
	close(fd[1]);
	s->infile = fd[0];
	return (0);
}

int	ft_openread(char *file)
{
	int	fd;
	int	empty_fd[2];

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_puterror_fd("try to open a directory", 2);
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
		ft_puterror_fd("try to open a directory", 2);
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
		ft_puterror_fd("try to open a directory", 2);
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

int	ft_openredir(char *file, int type, t_id *id)
{
	id = id->next;
	if (type == 7)
		return (ft_openwrite(file));
	else if (type == 8)
		return (ft_openwrited(file));
	else if (type == 9)
		return (ft_openread(file));
	return (-1);
}
