/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:10:29 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/08 18:08:04 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

char	*ft_cutheredocdoll(char *str, char *ret)
{
	t_env	*env;
	char	**split;
	int	i;

	env = g_data.minishell_env;
	split = ft_split(str, ret);
	i = 0;
	while (env != NULL)
	{
		if (ft_strncmp(ret + 1, env->key,
			ft_strlen(env->key) + 1) == 0)
		{
			free(ret);
			ret = ft_strdup(env->value);
			break;
		}
		else
			env = env->next;
	}
	if (env == NULL)
	{
		free(ret);
		ret = ft_strdup("");
	}
	while (split[i] != NULL)
	{
		if (split[i][0] == '$')
		{
			free(split[i]);
			split[i] = ret;
			free(str);
			str = '\0'
			i = 0;
			while (split[i] != NULL)
			{
				str = ft_strjoin();
				//faire une fonction joinsplit !
			}
		}
	}

}

char	*ft_heredocdoll(char *str)
{
	int	i;
	int	j;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i;
			i++;
			while (str[i] && ft_isalpha(str[i]) == 1)
				i++;
			ret = ft_strndup(str + j, (i - j));
			str = ft_curheredocdoll(str, ret, i, j);
		}
		i++;
	}
	if (ret == NULL)
		return (str);
	return (ret);
}

void	ft_convertdoll(t_id *id, t_env *env)
{
	int		i;

	i = 0;
	while (env != NULL)
	{
		if (ft_strncmp(id->data, env->key, ft_strlen(env->key) + 1) == 0)
		{
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
