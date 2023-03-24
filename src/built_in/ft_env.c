/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:14 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/24 16:27:22 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_env(t_cmd *command)
{
	t_env	*current;

	current = g_data.minishell_env;
	if (command->cmd[1])
	{
		ft_putstr_fd("minishell: env: ", command->outfile);
		ft_putstr_fd(command->cmd[1], command->outfile);
		ft_putendl_fd(": no such file or directory", command->outfile);
		*g_data.status_code = 127;
		return ;
	}
	while (current)
	{
		if (current->value)
		{
			ft_putstr_fd(current->key, command->outfile);
			ft_putstr_fd("=", command->outfile);
			ft_putendl_fd(current->value, command->outfile);
		}
		current = current->next;
	}
	*g_data.status_code = 0;
}
