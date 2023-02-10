/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:08:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/10 10:19:40 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static void	ft_execute(void)
// {
// 	t_cmd	*commands;

// 	commands = data.cmds;
// 	while (commands)
// 	{
// 		if (commands->type == BASIC)
// 			ft_do_basic_cmd(commands);
// 		else if (commands->type == BUILT_IN)
// 			ft_do_built_in_cmd(commands);
// 		else if (commands->type == PIPE)
// 			ft_do_pipe_cmd(commands);
// 		commands = commands->next;
// 	}
// }

void	ft_new_command(void)
{
	char	*str;

	str = 0;
	str = readline(PROMPT_MESS);
	if (str == NULL)
	{
		// write exit on prompt
		rl_replace_line("", 0);
		rl_redisplay();
		ft_exit();
	}
	else if (str[0] == 0)
	{
		free(str);
	}
	else
	{
		// ft_parsing(str);
		// ft_execute();
		ft_env();
	}
}

void	ft_sig_handle(int sig)
{
	if (sig == SIGINT)
	{
		// remove ^C
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
