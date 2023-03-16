/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 17:47:11 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/16 11:50:58 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

t_pid	*ft_new_pid(void)
{
	t_pid	*current;
	t_pid	*new;

	new = malloc(sizeof(t_pid));
	new->next = 0;
	current = g_data.pids;
	if (current)
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
	else
		g_data.pids = new;
	return (new);
}

void	ft_wait_all_pids(void)
{
	t_pid	*current;
	t_pid	*next;

	current = g_data.pids;
	while (current)
	{
		next = current->next;
		waitpid(current->pid, g_data.status_code, 0);
		current = next;
	}
	g_data.pids = 0;
}
