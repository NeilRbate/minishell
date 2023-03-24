/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:49:03 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/24 16:44:34 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

static void	ft_export_no_args(t_cmd *command)
{
	t_env	*current;

	current = g_data.minishell_env;
	while (current)
	{
		if (!ft_strncmp(current->key, "_", 2))
		{
			current = current->next;
		}
		else
		{
			ft_putstr_fd("declare -x ", command->outfile);
			ft_putstr_fd(current->key, command->outfile);
			if (current->value)
			{
				ft_putstr_fd("=", command->outfile);
				ft_putchar_fd('"', command->outfile);
				ft_putstr_fd(current->value, command->outfile);
				ft_putchar_fd('"', command->outfile);
			}
			ft_putchar_fd('\n', command->outfile);
			current = current->next;
		}
	}
	*g_data.status_code = 0;
}

static int	ft_export_get_keyval(char *keyval, char **key, char **value)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (keyval[i])
	{
		if (keyval[i] == '=')
		{
			*key = ft_substr(keyval, 0, i);
			if (keyval[i + 1] == '\0')
				*value = 0;
			else
				*value = ft_strdup(keyval + i + 1);
			return (1);
		}
		i++;
	}
	*key = ft_strdup(keyval);
	*value = 0;
	return (1);
}

static int	ft_export_key_is_valid(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_export_args(char **to_export)
{
	char	**list;
	int		i;
	char	*key;
	char	*value;

	i = 0;
	list = to_export;
	while (list[i])
	{
		if (ft_export_get_keyval(list[i], &key, &value))
		{
			if (ft_export_key_is_valid(key))
			{
				ft_env_add(key, value);
				*g_data.status_code = 0;
			}
			else
			{
				ft_export_error_message(key);
			}
			free(key);
			free(value);
		}
		i++;
	}
}

static void	ft_add_tab(char *to_add, char ***list)
{
	
}

static char	**ft_set_keyval(char **list)
{
	char	**new;
	char	*tmp;
	int		i;

	if (!list[0])
		return (0);
	i = 0;
	tmp = 0;
	while (list[i])
	{
		if (i > 0 && (list[i] == '"' || list[i] == 39))
		{
			tmp = ft_strjoin(list[i - 1], list[i + 1]);
			ft_add_tab(tmp, &new);
			free(tmp);
			i += 3;
		}
		else
		{
			ft_add_tab(list[i], &new);
			i++;
		}
	}
	return (0);
}

void	ft_export(t_cmd *command)
{
	char	**export;

	export = ft_set_keyval(command->cmd + 1);
	if (!export)
		ft_export_no_args(command);
	else
		ft_export_args(export);
}
