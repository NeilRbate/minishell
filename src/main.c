/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/13 17:30:11 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static void	echo_ctl(int n)
{
	struct termios	term;

	tcgetattr(0, &term);
	if (n)
		term.c_lflag |= ECHOCTL;
	else
		term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 2)
	{
		ft_putendl_fd("Error\nWrong number of argument", 2);
		return (0);
	}
	(void)argv;
	echo_ctl(0);
	ft_get_env(envp);
	signal(SIGINT, ft_sig_handle);
	while (1)
		ft_new_command();
	return (0);
}
