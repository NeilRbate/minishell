/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:01:22 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/13 12:50:02 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_export_no_args(void)
{
	char	**env;
	int		i;
	char	*key;
	int		j;

	i = 0;
	env = data.minishell_env;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		key = ft_substr(env[i], 0, j + 1);
		printf("declare -x %s%c%s%c\n", key, '"', env[i] + j + 1, '"');
		i++;
	}
	data.status_code = 0;
}

int	ft_env_key_exist(char *key)
{
	char	**env;
	int		i;

	env = data.minishell_env;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(key, env[i], ft_strlen(key)))
			return (1);
		i++;
	}
	return (0);
}

void	ft_check_n_add(char *key, char *value)
{
	char	*ckey;
	int		i;

	ckey = ft_substr(key, 0, ft_strlen(key) - 1);
	i = 0;
	while (ckey[i])
	{
		if (ft_isalnum(ckey[i]) == 0 && ckey[i] != '_')
		{
			data.status_code = 1;
			ft_putendl_fd("---\nEXPORT FAIL\n---", 2);
			free(ckey);
			return ;
		}
		i++;
	}
	if (ft_env_key_exist(key))
	{
		ft_del_env_element(key);
		ft_add_env_element(ckey, value);
	}
	else
	{
		ft_add_env_element(ckey, value);
	}
	free(ckey);
	data.status_code = 0;
}

void	ft_export_var(char **var_lst)
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	char	**lst;

	lst = var_lst;
	i = 1;
	while (lst[i])
	{
		j = 0;
		while (lst[i][j] != '=')
			j++;
		key = ft_substr(lst[i], 0, j + 1);
		value = ft_strdup(lst[i] + j + 1);
		ft_check_n_add(key, value);
		free(key);
		free(value);
		i++;
	}
}

void	ft_export(t_cmd *command)
{
	pid_t	child;
	char	**cmd;

	child = fork();
	if (child == 0)
	{
		cmd = command->cmd;
		if (cmd[1])
			ft_export_var(cmd);
		else
		{
			ft_export_no_args();
		}
		exit(0);
	}
	waitpid(child, 0, 0);
}
