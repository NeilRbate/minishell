/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:09 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/20 10:49:16 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

static void	ft_go_home(void)
{
	char	*home;
	char	*current_pwd;

	if (ft_env_key_exist("HOME"))
	{
		home = ft_get_env_value("HOME");
		current_pwd = getcwd(0, 1000);
		ft_env_add("OLDPWD", current_pwd);
		free(current_pwd);
		chdir(home);
		ft_env_add("PWD", home);
		free(home);
		*g_data.status_code = 0;
	}
	else
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		*g_data.status_code = 1;
	}
}

static void	ft_go_to(char *str)
{
	char	*current_pwd;

	if (open(str, O_DIRECTORY) != -1)
	{
		current_pwd = getcwd(0, 1000);
		ft_env_add("OLDPWD", current_pwd);
		free(current_pwd);
		chdir(str);
		current_pwd = getcwd(0, 1000);
		ft_env_add("PWD", current_pwd);
		free(current_pwd);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": Not a directory", 2);
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
		ft_go_to(to_go);
}
