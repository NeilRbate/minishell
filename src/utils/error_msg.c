/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 08:45:54 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/09 11:29:26 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_error_msg(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
}

void	ft_set_underscore(void)
{
	char	**strs;
	int		i;

	i = 0;
	if (g_data.cmds && g_data.cmds->type == BUILT_IN)
	{
		strs = g_data.cmds->cmd;
		while (strs[i])
			i++;
		i--;
		ft_env_replace("_", strs[i]);
	}
}

