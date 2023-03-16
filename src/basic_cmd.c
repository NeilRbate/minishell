/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:43 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/16 13:39:04 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

char	*ft_strtrijoin(char const *s1, char const *s2, char const *s3)
{
	int		i;
	int		j;
	char	*str;
	int		len;

	i = 0;
	j = 0;
	if (!(s1) || !(s2))
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	str = malloc(sizeof(char) * len + 1);
	if (!(str))
		return (0);
	while (s1[i])
			str[j++] = s1[i++];
	i = 0;
	while (s2[i])
			str[j++] = s2[i++];
	i = 0;
	while (s3[i])
			str[j++] = s3[i++];
	str[j] = '\0';
	return (str);
}

static void	ft_dup_in(int infile, int outfile)
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

static void	ft_dup_out(int infile, int outfile)
{
	if (infile != 0)
	{
		close(infile);
	}
	if (outfile != 1)
	{
		close(outfile);
	}
}

void	ft_try_exe(t_cmd *cmd)
{
	int		i;
	char	*command;

	i = 0;
	ft_dup_in(cmd->infile, cmd->outfile);
	if (access(cmd->cmd[0], F_OK) == 0)
		if (execve(cmd->cmd[0], cmd->cmd, g_data.exec_env) == -1)
			perror("minishell: ");
	while (g_data.cmd_path[i])
	{
		command = ft_strtrijoin(g_data.cmd_path[i], "/", cmd->cmd[0]);
		if (access(command, F_OK) == 0)
			if (execve(command, cmd->cmd, g_data.exec_env) == -1)
				perror("minishell: ");
		free(command);
		i++;
	}
}

void	ft_do_basic_cmd(t_cmd *cmd)
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
		if (!ft_strncmp(cmd->cmd[0], "/", 2))
			execve(cmd->cmd[0], cmd->cmd, g_data.exec_env);
		else
			ft_try_exe(cmd);
		ft_error_msg(cmd->cmd[0]);
		exit(1);
	}
	else
		ft_dup_out(cmd->infile, cmd->outfile);
}
