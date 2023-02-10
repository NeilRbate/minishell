/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/10 10:07:26 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 2)
	{
		ft_putendl_fd("Error\nWrong number of argument", 2);
		return (0);
	}
	(void)argv;
	ft_get_env(envp);
	signal(SIGINT, ft_sig_handle);
	while (1)
		ft_new_command();
	return (0);
}
