/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:48:38 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/29 13:49:42 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static char	*ft_check_access_pipe(char *to_test)
{
	int		i;
	char	*try;

	i = 0;
	try = 0;
	if (access(to_test, F_OK) == 0)
		return (ft_strdup(to_test));
	else if (g_data.cmd_path)
	{
		while (g_data.cmd_path[i])
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
	return (0);
}

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
	access_cmd = ft_check_access_pipe(cmd->cmd[0]);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		ft_dup_n_close(cmd);
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
		ft_error_msg(cmd->cmd[0]);
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
