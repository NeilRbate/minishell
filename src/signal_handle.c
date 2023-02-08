/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:08:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/08 08:52:02 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_new_command(void)
{
	char	*str;
	t_cmd	*cmds;

	str = 0;
	str = readline(PROMPT_MESS);
	if (str == NULL)
	{
		// write exit on prompt
		rl_replace_line("", 0);
		rl_redisplay();
		exit(0);
	}
	else if (str[0] == 0)
	{
		free(str);
		return (ft_new_command());
	}
	else
	{
		add_history(str);
		cmds = ft_parsing(str);
	//	ft_print_cmdlist(cmds);
//		ft_execute(cmds);
		free(str);
	}
}

void	ft_sig_handle(int sig)
{
	signal(SIGINT, ft_sig_handle);
	if (sig == SIGINT)
	{
		// remove ^C
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
