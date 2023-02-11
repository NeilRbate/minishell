/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:01:22 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/11 11:17:51 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_no_args(void)
{
	t_env	*current;

	current = data.minishell_env;
	while (current)
	{
		printf("declare -x %s=%c%s%c\n", current->key, '"', current->value, '"');
		current = current->next;
	}
	data.status_code = 0;
}

static void	ft_check_n_add(char	*str)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	value = ft_strdup(str + i);
	if (str[i - 1] == '=')
		i--;
	key = ft_substr(str, 0, i);
	ft_add_env_element(key, value);
	free(key);
	free(value);
}

static void	ft_export_var(char **strs)
{
	int		i;

	i = 1;
	while (strs[i])
	{
		ft_check_n_add(strs[i]);
		i++;
	}
}

void	ft_export(t_cmd *command)
{
	pid_t	child;
	char	**cmd;

	child = fork();
	cmd = command->cmd;
	if (child == 0)
	{
		if (cmd[1] == 0)
			ft_no_args();
		else
		{
			ft_export_var(cmd);
		}
		data.status_code = 0;
		exit(0);
	}
	waitpid(child, 0, 0);
}