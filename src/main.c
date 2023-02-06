/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/06 18:03:41 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	ft_handle_signal(int sig);

void	ft_new_command(void)
{
	char	*str;

	str = 0;
	signal(SIGINT, ft_handle_signal);
	str = readline("minishell-1.0$ ");
	if (str[0] == 4)
		ft_new_command();

}

void	ft_handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_new_command();
	}
	if (sig == SIGQUIT)
	{
		printf("Quit : 3\n");
	}
}

int	main(void)
{
	while (1)
	{
		signal(SIGINT, ft_handle_signal);
	}
	return (0);
}
