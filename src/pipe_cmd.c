/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:48:38 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/04 14:00:23 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

void	ft_dup_n_close(int infile, int outfile)
{
	if (infile != 0)
	{
		dup2(infile, 0);
		close(infile);
	}
	if (outfile != 1)
	{
		dup2(outfile, 1);
		close(outfile);
	}
}

void	ft_execute_pipe(t_cmd *cmd, int infile, int outfile)
{
	pid_t	child;
	int		i;
	char	*command;

	child = fork();
	if (child == 0)
	{
		i = 0;
		ft_dup_n_close(infile, outfile);
		char	*str = malloc(sizeof(char) * 10 + 1);
		read(infile, str, 10);
		str[10] = '\0';
		printf("%s\n", str);
		while (g_data.cmd_path[i])
		{
			command = ft_strtrijoin(g_data.cmd_path[i], "/", cmd->cmd[0]);
			if (access(command, F_OK) == 0)
				if (execve(command, cmd->cmd, g_data.exec_env) == -1)
					perror("minishell: ");
			free(command);
			i++;
		}
		ft_error_msg(cmd->cmd[0]);
		exit(0);
	}
	waitpid(child, g_data.status_code, 0);
}

void	ft_do_pipe_cmd(t_cmd *cmd)
{
	int		outin[2];
	t_cmd	*current;

	current = cmd;
	pipe (outin);
	printf("ff");
	ft_execute_pipe(current, current->infile, outin[1]);
	current = current->next;
	while (current)
	{
		if (current->next)
			ft_execute_pipe(current, outin[0], outin[1]);
		else
			ft_execute_pipe(current, outin[0], current->outfile);
		current = current->next;
	}
	close(outin[0]);
	close(outin[1]);
}


