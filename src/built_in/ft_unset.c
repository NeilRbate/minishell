/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:09:36 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/11 11:35:54 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_unset_key(char *str)
{
	t_env	*current;
	t_env	*to_del;

	if (ft_check_key(str) == 0)
	{
		ft_putstr_fd("minishell: unset: '", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return ;
	}
	current = data.minishell_env;
	while (current)
	{
		if (ft_strncmp(str, current->next->key, ft_strlen(str) + 1) == 0)
		{
			to_del = current->next;
			current->next = to_del->next;
			free(to_del->key);
			free(to_del->value);
			free(to_del);
			return ;
		}
		current = current->next;
	}
}

void	ft_unset(t_cmd *command)
{
	pid_t	child;
	char	**keys;
	int		i;

	child = fork();
	if (child == 0)
	{
		keys = command->cmd;
		i = 1;
		while (keys[i])
		{
			ft_unset_key(keys[i]);
			i++;
		}
		exit(0);
	}
	waitpid(child, 0, 0);
}
