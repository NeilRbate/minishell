/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:58:40 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/10 10:59:00 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_go_home(void)
{
	
}

void	ft_cd(t_cmd *command)
{
	char	**strs;
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		strs = command->cmd;
		if (!strs[1])
			ft_go_home();
		else
		{
			chdir(strs[1]);
		}
	}
	waitpid(child, 0, 0);
}
