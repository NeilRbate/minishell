/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:49:03 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/02 12:43:37 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

static void	ft_export_no_args(t_cmd *command)
{
	t_env	*current;

	current = g_data.minishell_env;
	while (current)
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
	*g_data.status_code = 0;
}

static void	ft_export_error_message(char *keyval)
{
	char	*tmp;
	char	*tmpp;

	tmp = ft_strjoin("minishell: export: `", keyval);
	tmpp = ft_strjoin(tmp, "': not a valid identifier");
	free(tmp);
	ft_putendl_fd(tmpp, 2);
	free(tmpp);
	*g_data.status_code = 1;
}

static int	ft_export_valid_key(char *key, char	*keyval)
{
	int		i;
	char	*str;

	str = key;
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_export_error_message(keyval);
			*g_data.status_code = 1;
			return (0);
		}
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
	int		j;

	i = -1;
	list = to_export;
	while (list[++i])
	{
		j = 0;
		while (list[i][j] && list[i][j] != '=')
			j++;
		key = ft_substr(list[i], 0, j);
		if (list[i][j + 1])
			value = ft_strdup(list[i] + j + 1);
		else
			value = 0;
		if (ft_export_valid_key(key, list[i]))
		{
			ft_env_add(key, value);
			*g_data.status_code = 0;
		}
		free(key);
		free(value);
	}
}

void	ft_export(t_cmd *command)
{
	char	**export;

	export = command->cmd;
	if (!export[1])
		ft_export_no_args(command);
	else
		ft_export_args(export + 1);
}
