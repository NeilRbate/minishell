/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:31 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/27 16:35:11 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

int	ft_env_key_exist(char *key)
{
	t_env	*current;

	current = g_data.minishell_env;
	while (current)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key) + 1))
			return (1);
		current = current->next;
	}
	return (0);
}

void	ft_env_replace(char *key, char *value)
{
	t_env	*current;

	current = g_data.minishell_env;
	while (current)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key) + 1))
		{
			if (current->value)
				free(current->value);
			if (value)
				current->value = ft_strdup(value);
			else
				current->value = 0;
		}
		current = current->next;
	}
}

static int	ft_get_env_len(void)
{
	t_env	*current;
	int		len;

	current = g_data.minishell_env;
	len = 0;
	while (current)
	{
		len++;
		current = current->next;
	}
	return (len);
}

void	ft_set_env_for_exec(void)
{
	char	**new;
	t_env	*current;
	char	*tmp;
	int		i;

	new = malloc(sizeof(char *) * (ft_get_env_len() + 1));
	current = g_data.minishell_env;
	i = 0;
	while (current)
	{
		tmp = ft_strjoin(current->key, "=");
		new[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		i++;
		current = current->next;
	}
	new[i] = 0;
	g_data.exec_env = new;
	ft_path_setup();
}

char	*ft_get_env_value(char *key)
{
	char	*value;
	t_env	*current;

	current = g_data.minishell_env;
	while (current)
	{
		if (!ft_strncmp(current->key, key, ft_strlen(key) + 1))
		{
			value = ft_strdup(current->value);
			return (value);
		}
		current = current->next;
	}
	return (NULL);
}
