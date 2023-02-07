/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:08:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/07 12:45:57 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_ex.h"

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
		ft_echo(str, 0, 1);
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