/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:48:38 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/17 10:56:45 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static void	ft_new_pipe(void)
{
	t_pipe	*current;
	t_pipe	*new;

	new = malloc(sizeof(t_pipe));
	pipe(new->rdwr);
	new->next = 0;
	if (g_data.pipes == 0)
		g_data.pipes = new;
	else
	{
		current = g_data.pipes;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

static void	ft_exec_cmd(t_cmd *cmd)
{
	if (cmd->type == BUILT_IN)
		ft_do_built_in_cmd(cmd);
	else if (cmd->type == BASIC)
		ft_do_basic_cmd(cmd);
}

void	ft_do_pipe_cmd(t_cmd *cmd)
{
	t_pipe	*current_pipe;
	t_cmd	*current;

	ft_new_pipe();
	current_pipe = g_data.pipes;
	current = cmd;
	close(current_pipe->rdwr[0]);
	current->outfile = current_pipe->rdwr[1];
	ft_exec_cmd(current);
	while (current)
	{
		if (current->next)
		{
			ft_new_pipe();
			current->infile = current_pipe->rdwr[0];
			current_pipe = current_pipe->next;
			current->outfile = current_pipe->rdwr[1];
			ft_exec_cmd(current);
		}
		else
		{
			current->infile = current_pipe->rdwr[0];
			ft_exec_cmd(current);
			close(current_pipe->rdwr[0]);
			close(current_pipe->rdwr[1]);
		}
		printf("FF\n");		current = current->next;
	}
}
