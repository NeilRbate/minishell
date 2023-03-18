/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:09 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/18 14:15:19 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

// static void	ft_cd_error_msg(char *str)
// {
// 	ft_putstr_fd("minishell: cd: ", 2);
// 	perror(str);
// }

void	ft_go_home(void)
{
	char	*home;
	char	*current_pwd;

	if (ft_env_key_exist("HOME"))
	{
		home = ft_get_env_value("HOME");
		current_pwd = getcwd(0, 100);
		ft_env_add("ODLPWD", current_pwd);
		free(current_pwd);
		*g_data.status_code = 0;
	}
	else
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		*g_data.status_code = 1;
	}
}

void	ft_cd(t_cmd *cmd)
{
	char	*to_go;

	to_go = cmd->cmd[1];
	if (!to_go)
		ft_go_home();
	else
		;
}
