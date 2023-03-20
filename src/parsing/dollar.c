/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:10:29 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/20 13:14:25 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

char	*ft_cutheredocdoll(char *ret)
{
	t_env	*env;

	env = g_data.minishell_env;
	if (ft_strncmp(ret, "$?", 2) == 0)
		return (free(ret), ret = ft_itoa(*g_data.status_code), ret);
	while (env != NULL)
	{
		if (ft_strncmp(ret + 1, env->key,
				ft_strlen(env->key) + 1) == 0)
		{
			if (ret != NULL)
				free(ret);
			//if (env->value == NULL)
			//	ret = ft_strdup("");
			//else
				ret = ft_strdup(env->value);
			break ;
		}
		else
			env = env->next;
	}
	if (env == NULL)
	{
		free(ret);
		ret = ft_strdup("");
	}
	return (ret);
}

char	*ft_heredocdoll(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	ret = NULL;
	while (str[i])
	{
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) == 1 || str[i + 1] == '?'))
		{
			j = i;
			i++;
			ret = ft_retd(i, j, str);
			break ;
		}
		i++;
	}
	if (ret == NULL)
		return (str);
	if (i == 0 && str[j + 1] == '\0')
		return (free(str), ret);
	return (free(str), ret);
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
		id->type = 20;
		id->data = ft_strdup("");
	}
	free(id->prev->data);
	id->prev->data = ft_strdup("");
	id->prev->type = 0;
}

t_id	*ft_dollctrl(t_id *id, int *i)
{
	t_id	*stock;

	stock = id;
	while (id->prev != NULL)
	{
		id = id->prev;
		if (id->type == 10)
			return (ft_joindoll(stock));
		else if (id->type != 5)
		{
			id = stock;
			break ;
		}
	}
	id = id->next;
	if (id->type == 0)
	{
		ft_doll(id);
		id->prev->type = 20;
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
