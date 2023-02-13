/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 07:44:12 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/13 11:27:49 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_update_shlvl(void)
{
	char	**env;
	int		sh;
	char	*lvl;
	int		i;

	i = 0;
	env = data.minishell_env;
	while (env[i])
	{
		if (!ft_strncmp("SHLVL=", env[i], 6))
		{
			sh = ft_atoi(env[i] + 6);
			sh += 1;
			lvl = ft_itoa(sh);
			free(env[i]);
			env[i] = ft_strjoin("SHLVL=", lvl);
			free(lvl);
			break ;
		}
		i++;
	}
}

void	ft_add_env_element(char *key, char *value)
{
	int		i;
	char	**env;
	char	**new_env;
	char	*tmp;

	env = data.minishell_env;
	tmp = 0;
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	ft_freesplit(env);
	tmp = ft_strjoin(key, "=");
	new_env[i++] = ft_strjoin(tmp, value);
	free(tmp);
	new_env[i] = 0;
	data.minishell_env = new_env;
}

void	ft_del_env_element(char *key)
{
	char	**env;
	int		i;
	int		j;
	char	**new_env;

	env = data.minishell_env;
	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (!(ft_strncmp(key, env[i], ft_strlen(key))))
			i++;
		else
		{
			new_env[j++] = ft_strdup(env[i++]);
		}
	}
	new_env[j] = 0;
	ft_freesplit(env);
	data.minishell_env = new_env;
}

static void	ft_get_path(void)
{
	char	**env;
	char	**paths;
	int		i;

	i = 0;
	paths = 0;
	env = data.minishell_env;
	while (env[i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			paths = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	data.cmd_path = paths;
}

void	ft_get_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = 0;
	data.minishell_env = new_env;
	ft_update_shlvl();
	ft_get_path();
}
