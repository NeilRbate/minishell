/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:08:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/06 16:47:47 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static void	ft_execute(void)
{
	t_cmd	*command;
	pid_t	child;

	command = g_data.cmds;
	if (command == NULL)
		return ;
	if (command->next)
	{
		child = fork();
		if (child == 0)
		{
			ft_do_pipe_cmd(command);
			exit(0);
		}
		waitpid(child, g_data.status_code, 0);
		return ;
	}
	if (command->type == BUILT_IN)
		ft_do_built_in_cmd(command);
	else if (command->type == BASIC)
	{
		ft_set_env_for_exec();
		ft_do_basic_cmd(command);
		ft_free_split(g_data.exec_env);
	}
}

void	ft_new_command(void)
{
	char	*str;

	str = 0;
	str = readline(PROMPT_MESS);
	if (str == NULL)
	{
		ft_putendl_fd("exit", 0);
		exit(0);
	}
	else if (str[0] == 0)
	{
		free(str);
	}
	else
	{
		add_history(str);
		g_data.cmds = ft_parsing(str);
		ft_execute();
		free(str);
		ft_del_cmdlist(g_data.cmds);
	}
}

void	ft_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
