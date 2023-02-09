/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 07:44:12 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/09 11:06:27 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static void	ft_update_shlvl(char **env)
// {

// }

void	ft_add_element(char *key, char *value, t_env **minishell_env)
{
	t_env	*current;
	t_env	*new;

	new = malloc(sizeof(t_env));
	new->next = 0;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (*minishell_env == 0)
		*minishell_env = new;
	else
	{
		current = *minishell_env;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	ft_get_env(char **envp)
{
	t_env	*new;
	int		i;
	char	**splited;

	i = 0;
	data.minishell_env = 0;
	new = 0;
	while (envp[i])
	{
		splited = ft_split(envp[i], '=');
		ft_add_element(splited[0], splited[1], &new);
		ft_freesplit(splited);
		i++;
	}
	data.minishell_env = new;
}
