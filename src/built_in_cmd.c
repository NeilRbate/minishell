/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:47 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/31 12:00:10 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

void	ft_do_built_in_cmd(t_cmd *command)
{
	char	*str;

	str = command->cmd[0];
	if (!ft_strncmp(str, "echo", 5))
		ft_echo(command);
	else if (!ft_strncmp(str, "env", 4))
		ft_env(command);
	else if (!ft_strncmp(str, "exit", 5))
		ft_exit(command);
	else if (!ft_strncmp(str, "export", 7))
		ft_export(command);
	else if (!ft_strncmp(str, "unset", 6))
		ft_unset(command);
	else if (!ft_strncmp(str, "cd", 3))
		ft_cd(command);
	else if (!ft_strncmp(str, "pwd", 4))
		ft_pwd(command);
}
