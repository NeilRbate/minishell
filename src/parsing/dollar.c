/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:10:29 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/03 13:11:30 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_convertdoll(t_id *id, t_env *env)
{
	int		i;

	i = 0;
	while (env != NULL)
	{
		if (ft_strncmp(id->data, env->key, ft_strlen(env->key)) == 0)
		{
			if (ft_strlen(env->key) != ft_strlen(id->data))
				break ;
			free(id->data);
			id->data = ft_strdup(env->value);
			i = 1;
			break ;
		}
		else
			env = env->next;
	}
	if (i == 0)
	{
		free(id->data);
		id->data = ft_strdup("");
	}
	free(id->prev->data);
	id->prev->data = ft_strdup("");
	id->prev->type = 0;
}

t_id	*ft_dollctrl(t_id *id, int *i)
{
	id = id->next;
	if (id->type == 0)
	{
		ft_doll(id);
		ft_del_idelem(id->prev);
	}		
	else
		id->prev->type = 0;
	*i += 1;
	return (id);
}

void	ft_doll(t_id *id)
{
	t_env	*env;

	env = g_data.minishell_env;
	if (ft_strncmp(id->data, "?", 1) == 0)
	{
		free(id->data);
		id->data = ft_itoa(*g_data.status_code);
		free(id->prev->data);
		id->prev->data = ft_strdup("");
		id->prev->type = 0;
	}
	else
		ft_convertdoll(id, env);
}
