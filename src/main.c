/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/04/04 10:29:57 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

void	ft_update_status_code(void)
{
	if (*g_data.status_code > 255 && *g_data.status_code != 258)
		*g_data.status_code = (*g_data.status_code / 256);
}

void	ft_set_signal_nothing(void)
{
	signal(SIGINT, ft_sig_handle_do_nothing);
	signal(SIGQUIT, ft_sig_handle_do_nothing);
}

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

static void	ft_init_global(void)
{
	g_data.cmds = 0;
	g_data.minishell_env = 0;
	g_data.exec_env = 0;
	g_data.status_code = 0;
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 2)
	{
		ft_putendl_fd("Error\nWrong number of argument", 2);
		return (0);
	}
	(void)argv;
	ft_init_global();
	ft_env_setup(envp);
	while (1)
	{
		ft_new_command();
	}
	return (0);
}
