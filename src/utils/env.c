/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 07:44:12 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/21 11:55:47 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

static void	ft_lst_add(t_env *new)
{
	t_env	*current;

	if (g_data.minishell_env == 0)
	{
		g_data.minishell_env = new;
	}
	else
	{
		current = g_data.minishell_env;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

static void	ft_update_shlvl(void)
{
	t_env	*current;
	int		current_lvl;

	current_lvl = 0;
	current = g_data.minishell_env;
	while (current)
	{
		if (!ft_strncmp(current->key, "SHLVL", 6))
		{
			current_lvl = ft_atoi(current->value);
			current_lvl += 1;
			free(current->value);
			current->value = 0;
			current->value = ft_itoa(current_lvl);
			return ;
		}
		current = current->next;
	}
	ft_env_add("SHLVL", "1");
}

void	ft_env_setup(char **envp)
{
	t_env	*new;
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	tmp = envp;
	while (tmp[i])
	{
		j = 0;
		new = malloc(sizeof(t_env));
		new->next = 0;
		while (tmp[i][j] && tmp[i][j] != '=')
			j++;
		new->key = ft_substr(tmp[i], 0, j);
		new->value = ft_strdup(tmp[i] + j + 1);
		ft_lst_add(new);
		i++;
	}
	ft_update_shlvl();
	g_data.status_code = malloc(sizeof(int));
}

void	ft_env_add(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->next = 0;
	new->key = ft_strdup(key);
	if (value != 0)
		new->value = ft_strdup(value);
	else
		new->value = 0;
	if (ft_env_key_exist(key))
	{
		free(new->key);
		free(new->value);
		free(new);
		ft_env_replace(key, value);
	}
	else
		ft_lst_add(new);
}

void	ft_env_del(char	*key)
{
	t_env	*current;
	t_env	*to_del;
	t_env	*prev;

	current = g_data.minishell_env;
	prev = 0;
	while (current)
	{
		if (!(ft_strncmp(current->key, key, ft_strlen(key) + 1)))
		{
			to_del = current;
			if (prev)
				prev->next = to_del->next;
			else
				g_data.minishell_env = to_del->next;
		}
		prev = current;
		current = current->next;
	}
	free(to_del->key);
	free(to_del->value);
	free(to_del);
}
