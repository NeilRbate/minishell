/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:17 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/16 10:29:32 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

static void	ft_contain_only_digits(char *str, int *exit_code)
{
	int	i;
	int	res;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putendl_fd("minishell: exit: ff: numeric argument required", 2);
			exit(255);
		}
		i++;
	}
	res = ft_atoi(str);
	if (res >= 255)
		res = res % 256;
	*exit_code = res;
}

static void	ft_get_exit_code(char **strs, int *exit_code)
{
	ft_contain_only_digits(strs[1], exit_code);
	if (strs[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		*g_data.status_code = 1;
		*exit_code = -1;
	}
}

void	ft_exit(t_cmd *command)
{
	int	exit_code;

	ft_putendl_fd("exit", 1);
	if (!command->cmd[1])
		exit (1);
	exit_code = -1;
	ft_get_exit_code(command->cmd, &exit_code);
	if (exit_code != -1)
		exit(exit_code);
}
