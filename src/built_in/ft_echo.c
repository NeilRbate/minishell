/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 12:25:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/11 09:11:22 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_is_option(char *str, int *option)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	else
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		*option += 1;
		return (1);
	}
}

void	ft_echo(t_cmd *cmdd)
{
	char	**cmd;
	int		i;
	pid_t	child;
	int		option;

	child = fork();
	if (child == 0)
	{
		cmd = cmdd->cmd;
		i = 1;
		option = 0;
		while (ft_is_option(cmd[i], &option))
			i++;
		while (cmd[i])
		{
			printf("%s", cmd[i]);
			if (cmd[i + 1])
				printf(" ");
			i++;
		}
		if (option == 0)
			printf("\n");
		exit(0);
	}
	waitpid(child, 0, 0);
}
