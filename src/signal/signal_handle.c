/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:08:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/13 13:25:04 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	echo_ctl(int n)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (n)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

static void	ft_execute(void)
{
	// t_cmd	*commands;

	// commands = data.cmds;
	// while (commands)
	// {
	// 	if (commands->type == BASIC)
	// 		ft_do_basic_cmd(commands);
	// 	else if (commands->type == BUILT_IN)
	// 		ft_do_built_in_cmd(commands);
	// 	// else if (commands->type == PIPE)
	// 	// 	ft_do_pipe_cmd(commands);
	// 	commands = commands->next;
	// }
	ft_cd(0);
}

void	ft_new_command(void)
{
	char	*str;

	str = 0;
	str = readline(PROMPT_MESS);
	if (str == NULL)
	{
		// rl_redisplay()
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
		// ft_parsing(str);
		ft_execute();
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
