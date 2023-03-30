/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:43 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/29 14:04:56 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static void	ft_set_signals(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->cmd[0], "cat", 3) || (\
	!ft_strncmp(cmd->cmd[0], "grep", 5) && cmd->cmd[1] == 0))
	{
		echo_ctl(1);
		signal(SIGINT, ft_sig_handle_nothing);
		signal(SIGQUIT, ft_sig_handle_nothing);
	}
}

char	*ft_check_access(char *to_test)
{
	int		i;
	char	*try;

	i = 0;
	try = 0;
	if (access(to_test, F_OK) == 0)
		return (ft_strdup(to_test));
	else if (g_data.cmd_path != 0)
	{
		try = ft_strtrijoin(g_data.cmd_path[i], "/", to_test);
		if (access(try, F_OK) == 0)
		{
			try = ft_strtrijoin(g_data.cmd_path[i], "/", to_test);
			if (access(try, F_OK) == 0)
			{
				*g_data.status_code = 0;
				return (try);
			}
			free(try);
			try = 0;
			i++;
		}
	}
	ft_error_msg(to_test);
	return (0);
}

void	ft_check_slash(char *str)
{
	if (!ft_strncmp(str, "/", 2))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": is a directory", 2);
		exit(126);
	}
}

static void	ft_double_minishell(void)
{
	signal(SIGINT, ft_sig_handle_doubleshell);
	signal(SIGQUIT, ft_sig_handle_doubleshell);
}

void	ft_do_basic_cmd(t_cmd *cmd)
{
	char	*access_cmd;

	ft_set_signals(cmd);
	access_cmd = ft_check_access(cmd->cmd[0]);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		dup2(cmd->infile, 0);
		dup2(cmd->outfile, 1);
		ft_check_slash(cmd->cmd[0]);
		if (access_cmd)
			execve(access_cmd, cmd->cmd, g_data.exec_env);
		close(cmd->infile);
		exit(127);
	}
	else
	{
		ft_double_minishell();
		free(access_cmd);
		if (cmd->outfile != 1)
			close(cmd->outfile);
		waitpid(cmd->pid, g_data.status_code, 0);
	}

}
