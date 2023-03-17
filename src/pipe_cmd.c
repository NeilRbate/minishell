/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:48:38 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/17 16:05:24 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static void	ft_do_first_pipe(t_cmd *cmd)
{
	pipe(cmd->pipe);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		close(cmd->pipe[0]);
		dup2(cmd->infile, 0);
		if (cmd->outfile == 1 && cmd->next)
			dup2(cmd->pipe[1], 1);
		else
			dup2(cmd->outfile, 1);
		if (cmd->type == BUILT_IN)
		{
			ft_do_built_in_cmd(cmd);
			exit(0);
		}
		else if (!ft_strncmp(cmd->cmd[0], "/", 2))
			execve(cmd->cmd[0], cmd->cmd, g_data.exec_env);
		else
			ft_try_exe(cmd);
		ft_error_msg(cmd->cmd[0]);
		exit(1);
	}
	else
	{
		close(cmd->pipe[1]);
		if (cmd->next && cmd->next->infile == 0)
			cmd->next->infile = dup(cmd->pipe[0]);
		close(cmd->pipe[0]);
	}
}

static void	ft_wait_all_pids(t_cmd *mds)
{
	t_cmd	*current;

	current = mds;
	while (current)
	{
		waitpid(current->pid, g_data.status_code, 0);
		current = current->next;
	}

}

void	ft_do_pipe_cmd(t_cmd *cmd)
{
	t_cmd	*current_cmd;

	current_cmd = cmd;
	echo_ctl(1);
	signal(SIGINT, ft_sig_handle_nothing);
	signal(SIGQUIT, ft_sig_handle_nothing);
	while (current_cmd)
	{
		ft_do_first_pipe(current_cmd);
		if (current_cmd->outfile != 1)
			close(current_cmd->outfile);
		if (current_cmd->next == 0)
			break ;
		current_cmd = current_cmd->next;
	}
	if (current_cmd->infile != 0)
		close(current_cmd->infile);
	ft_wait_all_pids(g_data.cmds);
}
