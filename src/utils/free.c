/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:37 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/17 14:26:17 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"
#include "../../include/parsing.h"

void	ft_free_split(char **tab)
{
	char	**tmp;
	int		i;

	tmp = tab;
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp[i]);
	free(tmp);
	tmp = 0;
}

void	ft_free_t_env(void)
{
	t_env	*current;
	t_env	*tmp;

	current = g_data.minishell_env;
	while (current)
	{
		tmp = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = tmp;
	}
	g_data.minishell_env = 0;
}

void	ft_free_global(void)
{
	if (g_data.cmd_path)
		ft_freesplit(g_data.cmd_path);
	if (g_data.cmds)
		ft_del_cmdlist(g_data.cmds);
	if (g_data.minishell_env)
		ft_free_t_env();
	if (g_data.status_code)
		free(g_data.status_code);
}
