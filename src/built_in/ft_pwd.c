/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:22 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/04 09:16:22 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_pwd(t_cmd *command)
{
	pid_t	child;
	t_env	*current;

	child = fork();
	if (child == 0)
	{
		current = g_data.minishell_env;
		while (current)
		{
			if (!ft_strncmp(current->key, "PWD", 4))
			{
				ft_putendl_fd(current->value, command->outfile);
			}
			current = current->next;
		}
		g_data.status_code = 0;
		exit(0);
	}
	waitpid(child, 0, 0);
}
