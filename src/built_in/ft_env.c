/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 08:17:47 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/09 10:55:06 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(void)
{
	pid_t	child;
	t_env	*current;

	child = fork();
	if (child == 0)
	{
		current = data.minishell_env;
		while (current)
		{
			printf("%s=%s\n", current->key, current->value);
			current = current->next;
		}
		data.status_code = 0;
		exit(0);
	}
	waitpid(child, 0, 0);
}
