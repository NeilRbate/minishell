/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:12:25 by jbarbate          #+#    #+#             */
/*   Updated: 2023/02/24 09:12:27 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

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
		ft_putstr_fd("pipex: ", 2);
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
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
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
	fd = open(file, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: ", 2);
		perror(file);
		return (-1);
	}
	return (fd);
}
