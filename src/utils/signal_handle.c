/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:08:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/14 15:29:07 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static void	ft_execute(void)
{
	t_cmd	*command;

	command = g_data.cmds;
	if (command->type == BUILT_IN)
		ft_do_built_in_cmd(command);
	else if (command->type == BASIC)
	{
		ft_set_env_for_exec();
		ft_do_basic_cmd(command);
		ft_free_split(g_data.exec_env);
	}
	else if (command->type == PIPE)
		ft_do_pipe_cmd(command);
}

void	ft_new_command(void)
{
	char	*str;

	str = 0;
	str = readline(PROMPT_MESS);
	if (str == NULL)
	{
		printf("exit\n");
		ft_exit();
	}
	else if (str[0] == 0)
	{
		free(str);
		return ;
	}
	else
	{
		add_history(str);
		/* ADD PARSING LINE FUNCTION HERE */
		/* THE RESULT MUST TO BE PUT IN g_data.cmds */
		/* THE STR GIVEN MUST TO BE FREED */
		t_cmd	*test = malloc(sizeof(t_cmd));
		test->cmd = ft_split(str, ' ');
		test->type = BASIC;
		g_data.cmds = test;
		ft_execute();
		free(str);
		ft_free_split(test->cmd);
		free(test);
		//
		return ;
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
