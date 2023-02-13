/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:45:43 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/13 09:07:32 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_do_built_in(t_cmd *command)
// {
// 	char	*str;

// 	str = command->cmd[0];
// 	if (!ft_strncmp(str, "echo", 5))
// 		ft_echo(command);
// 	else if (!ft_strncmp(str, "env", 4))
// 		ft_env();
// 	else if (!ft_strncmp(str, "exit", 5))
// 		ft_exit();
// 	else if (!ft_strncmp(str, "export", 4))
// 		ft_export(command);
// 	// else if (!ft_strncmp(str, "unset", 4))
// 	// 	ft_env();
// 	// else if (!ft_strncmp(str, "cd", 3))
// 	// 	ft_cd(command);
// 	else if (!ft_strncmp(str, "pwd", 4))
// 		ft_pwd();
// }