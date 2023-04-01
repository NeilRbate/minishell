/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:48:38 by efirmino          #+#    #+#             */
/*   Updated: 2023/04/01 17:56:11 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static char	*ft_basic_check_access(char *to_test)
{
	char	*tmp;
	char	**lst;
	int		i;

	if (access(to_test, F_OK) == 0)
		return (ft_strdup(to_test));
	tmp = ft_get_env_value("PATH");
	lst = ft_split(tmp, ':');
	if (lst == NULL)
		return (NULL);
	i = 0;
	while (lst[i])
	{
		tmp = ft_strtrijoin(lst[i++], "/", to_test);
		if (access(tmp, F_OK) == 0)
			return (tmp);
	}
	return (NULL);
}

static void	ft_execute_basic_cmd(t_cmd *cmd)
{
	char	*try;

	if (!ft_strncmp(cmd->cmd[0], "cat", 3) || (\
	!ft_strncmp(cmd->cmd[0], "grep", 5) && cmd->cmd[1] == 0))
	{
		echo_ctl(1);
		signal(SIGINT, ft_sig_handle_lock_cmd);
		signal(SIGQUIT, ft_sig_handle_lock_cmd);
	}
	try = ft_basic_check_access(cmd->cmd[0]);
	if (try && (open(cmd->cmd[0], O_DIRECTORY) > 0))
		ft_directory_quit_error_msg(cmd->cmd[0]);
	else if (errno == EACCES)
		ft_directory_quit_error_msg(cmd->cmd[0]);
	else if (access(try, F_OK) != 0)
		ft_cmd_not_found_quit_error_msg(cmd->cmd[0]);
	else if (execve(try, cmd->cmd, g_data.exec_env) == -1)
		ft_exec_quit_error_msg(cmd->cmd[0]);
	exit(1);
}

static void	ft_do_first_pipe(t_cmd *cmd)
{
	pipe(cmd->pipe);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		ft_dup_n_close(cmd);
		if (cmd->outfile == 1 && cmd->next)
			dup2(cmd->pipe[1], 1);
		else
			dup2(cmd->outfile, 1);
		if (cmd->type == BUILT_IN)
		{
			ft_do_built_in_cmd(cmd);
			exit(0);
		}
		else
			ft_execute_basic_cmd(cmd);
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
	signal(SIGINT, ft_sig_handle_do_nothing);
	signal(SIGQUIT, ft_sig_handle_do_nothing);
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
