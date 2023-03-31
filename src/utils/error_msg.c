/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 08:45:54 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/31 14:18:27 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_error_msg(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	ft_export_error_message(char *keyval)
{
	if (keyval[0] == '-')
	{
		ft_putstr_fd("minishell: export: ", 2);
		ft_putstr_fd(keyval, 2);
		ft_putendl_fd(": invalid option", 2);
		*g_data.status_code = 1;
	}
	else
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(keyval, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		*g_data.status_code = 1;
	}
}

void	ft_sig_handle_doubleshell(int sig)
{
	if (sig == SIGINT)
	{
		return ;
	}
	else if (sig == SIGQUIT)
	{
		return ;
	}
}

void	ft_prompt(int *i, char **str)
{
	if (*i == 0)
	{
		*str = readline(PROMPT_MESS);
		*i = 1;
	}
	else
	{
		*str = readline(PROMPT_MESS2);
		*i = 0;
	}
}
