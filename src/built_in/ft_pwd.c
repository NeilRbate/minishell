/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:59:00 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/10 10:33:24 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	t_env	*current;
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		current = data.minishell_env;
		while (current)
		{
			if (!ft_strncmp(current->key, "PWD", 4))
			{
				printf("%s\n", current->value);
				break ;
			}
			current = current->next;
		}
	}
	waitpid(child, 0, 0);
}
