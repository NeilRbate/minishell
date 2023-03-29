/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:08:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/29 13:01:22 by efirmino         ###   ########.fr       */
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
		ft_set_env_for_exec();
		ft_do_pipe_cmd(command);
		ft_free_split(g_data.exec_env);
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

	echo_ctl(0);
	signal(SIGINT, ft_sig_handle);
	signal(SIGQUIT, ft_sig_handle);
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
		free(str);
		ft_execute();
		ft_free_cmd(g_data.cmds);
	}
	if (*g_data.status_code > 255 && *g_data.status_code != 258)
		*g_data.status_code = (*g_data.status_code / 256);
}

void	ft_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		*g_data.status_code = 1;
		ft_putendl_fd("", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_redisplay();
	}
}

void	ft_sig_handle_nothing(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
		*g_data.status_code = 1;
		return ;
	}
	else if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit: 3", 1);
		*g_data.status_code = 1;
	}
}
