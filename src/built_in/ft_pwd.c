/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:59:00 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/13 12:48:07 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	**env;
	int		i;
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		env = data.minishell_env;
		i = 0;
		while (env[i])
		{
			if (!ft_strncmp("PWD=", env[i], 4))
			{
				printf("%s\n", env[i] + 4);
				data.status_code = 0;
				exit(0);
			}
			i++;
		}
		data.status_code = 0;
		exit(0);
	}
	waitpid(child, 0, 0);
}
