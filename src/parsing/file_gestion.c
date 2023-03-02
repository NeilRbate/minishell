/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:12:25 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/02 10:44:16 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	ft_heredoc(t_id *id, t_id *s)
{
	char	*str;
	char	*line;

	s = id;
	while (id->next != NULL && id->type != 0)
		id = id->next;
	if (id->type != 0)
		return (ft_putendl_fd("error: invalid syntax", 2), -1);
	str = malloc(1);
	if (!str)
		return (-1);
	str[0] = '\0';
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strnstr(line, id->data, ft_strlen(id->data))
			&& ft_strlen(id->data) == (ft_strlen(line) - 1))
			break ;
		str = ft_gstrjoin(str, line);
		free(line);
	}
	close(0);
	id->type = 20;
	ft_writepipe(s, str);
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
		ft_putendl_fd("error: Try to open a directory", 2);
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
