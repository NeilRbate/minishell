/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:25:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/07 12:51:02 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_ex.h"

void	ft_echo(char **arg, int infile, int outfile)
{
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		dup2(infile, 0);
		dup2(outfile, 1);
		close(infile);
		write(1, arg[2], ft_strlen(arg[2]));
		if (ft_strncmp(arg[1], "-n", 2) == 0)
			write(1, "\n", 1);
		close(outfile);
	}
	waitpid(child, 0, 0);
}