/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/17 14:19:03 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

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
	g_data.cmd_path = 0;
	g_data.cmds = 0;
	g_data.minishell_env = 0;
	g_data.exec_env = 0;
	g_data.status_code = 0;
}

static void	ft_path_setup(void)
{
	t_env	*current;

	current = g_data.minishell_env;
	while (current)
	{
		if (!ft_strncmp(current->key, "PATH", 5))
		{
			g_data.cmd_path = ft_split(current->value, ':');
			return ;
		}
		current = current->next;
	}
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
	ft_path_setup();
	while (1)
	{
		ft_new_command();
	}
	return (0);
}
