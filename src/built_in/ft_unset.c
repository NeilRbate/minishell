/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:25 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/29 13:41:02 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_unset_error_message(char *keyval)
{
	if (keyval[0] == '-')
	{
		ft_putstr_fd("minishell: unset: ", 2);
		ft_putstr_fd(keyval, 2);
		ft_putendl_fd(": invalid option", 2);
		*g_data.status_code = 1;
	}
	else
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(keyval, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		*g_data.status_code = 1;
	}
}

static int	ft_unset_valid_key(char *str)
{
	if (str && !ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	return (1);
}

static void	ft_unset_args(char **to_unset)
{
	char	**list;
	int		i;

	i = 0;
	list = to_unset;
	while (list[i])
	{
		if (ft_unset_valid_key(list[i]))
		{
			if (ft_env_key_exist(list[i]))
				ft_env_del(list[i]);
			*g_data.status_code = 0;
		}
		else
			ft_unset_error_message(list[i]);
		i++;
	}
}

void	ft_unset(t_cmd *command)
{
	char	**unset;

	unset = command->cmd;
	if (!unset[1])
		return ;
	else
		ft_unset_args(unset + 1);
}
