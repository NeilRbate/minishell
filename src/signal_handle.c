/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:08:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/09 14:51:08 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_execute(t_cmd *cmd)
{
	cmd = malloc(sizeof(t_cmd));
	cmd->cmd = malloc(sizeof(char *) * (10));
	cmd->cmd[0] = ft_strdup("echo");
	cmd->cmd[1] = ft_strdup("-nnnf");
	cmd->cmd[2] = ft_strdup("broooow");
	cmd->cmd[3] = 0;
	ft_echo(cmd);
}

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
		return (ft_new_command());
	}
	else if (ft_strncmp(str, "exit", 10) == 0)
		ft_exit();
	else
	{
		add_history(str);
		// data.cmds = ft_parsing(str);
		ft_execute(data.cmds);
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
