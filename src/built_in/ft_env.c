/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 08:17:47 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/13 09:31:39 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(void)
{
	pid_t	child;
	int		i;
	char	**env;

	child = fork();
	if (child == 0)
	{
		env = data.minishell_env;
		i = 0;
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
		data.status_code = 0;
		exit(0);
	}
	waitpid(child, 0, 0);
}
