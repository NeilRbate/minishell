/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:25 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/04 09:16:25 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

static void	ft_export_error_message(char *key)
{
	char	*tmp;
	char	*tmpp;

	tmp = ft_strjoin("minishell: unset: `", key);
	tmpp = ft_strjoin(tmp, "': not a valid identifier");
	free(tmp);
	ft_putendl_fd(tmpp, 2);
	free(tmpp);
	*g_data.status_code = 1;
}

static int	ft_unset_valid_key(char *key)
{
	int		i;
	char	*str;

	str = key;
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_export_error_message(str);
			*g_data.status_code = 1;
			return (0);
		}
		i++;
	}
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
		if (ft_unset_valid_key(list[i]) && ft_env_key_exist(list[i]))
		{
			ft_env_del(list[i]);
			*g_data.status_code = 0;
		}
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
