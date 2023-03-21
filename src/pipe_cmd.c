/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:48:38 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/20 15:09:01 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static void	ft_close_all_n_dup(t_cmd *cmd)
{
	close(cmd->pipe[1]);
	if (cmd->infile != 0)
		close(cmd->infile);
	if (cmd->next && cmd->next->infile == 0)
		cmd->next->infile = dup(cmd->pipe[0]);
	close(cmd->pipe[0]);
}

static void	ft_do_first_pipe(t_cmd *cmd)
{
	char	*access_cmd;

	pipe(cmd->pipe);
	access_cmd = ft_check_access(cmd->cmd[0]);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		close(cmd->pipe[0]);
		dup2(cmd->infile, 0);
		if (cmd->outfile == 1 && cmd->next)
			dup2(cmd->pipe[1], 1);
		else
			dup2(cmd->outfile, 1);
		ft_check_slash(cmd->cmd[0]);
		if (cmd->type == BUILT_IN)
		{
			ft_do_built_in_cmd(cmd);
			exit(0);
		}
		else if (access_cmd)
			execve(access_cmd, cmd->cmd, g_data.exec_env);
		exit(127);
	}
	else
		ft_close_all_n_dup(cmd);
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
