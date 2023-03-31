/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 16:33:44 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/31 11:15:06 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

static void	ft_create_n_add(char *key, char *value, t_env **to)
{
	t_env	*new;
	t_env	*current;

	new = malloc(sizeof(t_env));
	new->next = 0;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	if (*to == 0)
		*to = new;
	else
	{
		current = *to;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

static void	ft_cpy_env(t_env **to_print)
{
	t_env	*current;

	current = g_data.minishell_env;
	while (current)
	{
		ft_create_n_add(current->key, current->value, to_print);
		current = current->next;
	}
}

static t_env	*ft_get_order(t_env *env)
{
	t_env	*current;
	t_env	*haa;

	haa = env;
	current = haa->next;
	while (current)
	{
		if (ft_strncmp(haa->key, current->key, 50) > 0)
			haa = current;
		current = current->next;
	}
	return (haa);
}

static void	ft_env_del_order(char *key, t_env **to_print)
{
	t_env	*current;
	t_env	*to_del;
	t_env	*prev;

	current = *to_print;
	prev = 0;
	while (current)
	{
		if (!(ft_strncmp(current->key, key, ft_strlen(key) + 1)))
		{
			to_del = current;
			if (prev)
				prev->next = to_del->next;
			else
				*to_print = to_del->next;
		}
		prev = current;
		current = current->next;
	}
	free(to_del->key);
	free(to_del->value);
	free(to_del);
}

void	ft_export_in_order(t_cmd *command)
{
	t_env	*to_print;
	t_env	*haa;

	to_print = 0;
	ft_cpy_env(&to_print);
	while (to_print)
	{
		haa = ft_get_order(to_print);
		ft_putstr_fd("declare -x ", command->outfile);
		ft_putstr_fd(haa->key, command->outfile);
		if (haa->value)
		{
			ft_putstr_fd("=", command->outfile);
			ft_putchar_fd('"', command->outfile);
			ft_putstr_fd(haa->value, command->outfile);
			ft_putchar_fd('"', command->outfile);
		}
		ft_putchar_fd('\n', command->outfile);
		ft_env_del_order(haa->key, &to_print);
	}
}
