/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_bultin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:15:57 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/27 18:25:00 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	ft_isbuiltin(t_cmd *id)
{
	while (id != NULL)
	{
		if (!ft_strncmp(id->cmd[0], "echo", 5))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "env", 4))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "exit", 5))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "export", 7))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "unset", 6))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "cd", 3))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "pwd", 4))
			id->type = 1;
		id = id->next;
	}
}
