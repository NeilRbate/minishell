/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:08:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/09 17:52:36 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static void	ft_execute(void)
{
	t_cmd	*command;

	command = g_data.cmds;
	if (command == NULL)
		return ;
	if (command->next)
	{
		ft_do_pipe_cmd(command);
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
		ft_wait_all_pids();
	}
}

void	ft_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		*g_data.status_code = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
	}
}
