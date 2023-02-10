/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 07:44:12 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/10 09:27:28 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_update_shlvl(void)
{
	t_env	*current;
	int		shlvl;

	current = data.minishell_env;
	while (current)
	{
		if (!ft_strncmp(current->key, "SHLVL", 6))
		{
			shlvl = ft_atoi(current->value);
			shlvl += 1;
			free(current->value);
			current->value = ft_itoa(shlvl);
		}
		current = current->next;
	}
}

void	ft_add_env_element(char *key, char *value)
{
	t_env	*current;
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->next = 0;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (data.minishell_env == 0)
		data.minishell_env = new;
	else
	{
		current = data.minishell_env;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	ft_get_env(char **envp)
{
	int		i;
	char	**splited;

	i = 0;
	data.minishell_env = 0;
	while (envp[i])
	{
		splited = ft_split(envp[i], '=');
		ft_add_env_element(splited[0], splited[1]);
		ft_freesplit(splited);
		i++;
	}
	ft_update_shlvl();
}
