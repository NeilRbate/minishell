/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 08:45:54 by efirmino          #+#    #+#             */
/*   Updated: 2023/04/04 10:33:02 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

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

void	ft_exec_quit_error_msg(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	exit(1);
}

void	ft_cmd_not_found_quit_error_msg(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found", 2);
	exit(127);
}

void	ft_directory_quit_error_msg(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": is a directory", 2);
	exit(126);
}

void	ft_close_all_n_dup(t_cmd *cmd)
{
	close(cmd->pipe[1]);
	if (cmd->infile != 0)
		close(cmd->infile);
	if (cmd->next && cmd->next->infile == 0)
		cmd->next->infile = dup(cmd->pipe[0]);
	close(cmd->pipe[0]);
}
