/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:09 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/30 14:40:06 by efirmino         ###   ########.fr       */
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

static void	ft_set_gcwd_error(int fd)
{
	ft_putstr_fd("cd: error retrieving current ", 2);
	perror("directory: getcwd: cannot access parent directories");
	close(fd);
	*g_data.status_code = 0;
}

static void	ft_go_to(char *str)
{
	char	*current_pwd;
	int		fd;

	fd = open(str, O_DIRECTORY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(str);
		*g_data.status_code = 1;
		return ;
	}
	current_pwd = ft_get_env_value("PWD");
	ft_env_add("OLDPWD", current_pwd);
	free(current_pwd);
	chdir(str);
	current_pwd = getcwd(0, 1000);
	if (current_pwd == 0)
	{
		ft_set_gcwd_error(fd);
		return ;
	}
	ft_env_add("PWD", current_pwd);
	free(current_pwd);
	*g_data.status_code = 0;
	close(fd);
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
