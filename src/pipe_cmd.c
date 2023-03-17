/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:48:38 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/17 12:49:39 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static void	ft_new_pipe(void)
{
	t_pipe	*current;
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	pipe(new->rdwr);
	new->next = 0;
	if (g_data.pipes == 0)
		g_data.pipes = new;
	else
	{
		current = g_data.pipes;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	ft_exec_pipe(t_cmd *cmd)
{
	t_pid	*pid;
	int		i;

	i = 0;
	pid = ft_new_pid();
	echo_ctl(1);
	signal(SIGINT, ft_sig_handle_nothing);
	signal(SIGQUIT, ft_sig_handle_nothing);
	pid->pid = fork();
	if (pid->pid == 0)
	{
		dup2(cmd->infile, 0);
		dup2(cmd->outfile, 1);
		if (!ft_strncmp(cmd->cmd[0], "/", 2))
			execve(cmd->cmd[0], cmd->cmd, g_data.exec_env);
		else
			ft_try_exe(cmd);
		ft_error_msg(cmd->cmd[0]);
		exit(1);
	}
}

static void	ft_exec_cmd(t_cmd *cmd)
{
	if (cmd->type == BUILT_IN)
		ft_do_built_in_cmd(cmd);
	else if (cmd->type == BASIC)
		ft_exec_pipe(cmd);
}

void	ft_do_pipe_cmd(t_cmd *cmd)
{
	t_pipe	*current_pipe;
	t_cmd	*current;

	ft_new_pipe();
	current_pipe = g_data.pipes;
	current = cmd;
	// close(current_pipe->rdwr[0]);
	current->outfile = current_pipe->rdwr[1];
	ft_exec_cmd(current);
	while (current)
	{
		if (current->next)
		{
			ft_new_pipe();
			current->infile = current_pipe->rdwr[0];
			current_pipe = current_pipe->next;
			current->outfile = current_pipe->rdwr[1];
			ft_exec_cmd(current);
			// close(current_pipe->rdwr[0]);
			close(current_pipe->rdwr[1]);
		}
		else
		{
			current->infile = current_pipe->rdwr[0];
			ft_exec_cmd(current);
		}
		current = current->next;
	}
	close(current_pipe->rdwr[1]);
}
