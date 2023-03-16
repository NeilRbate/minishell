/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:48:38 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/16 10:33:44 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static void	ft_exec_pipe(t_cmd *cmd)
{
	if (cmd->type == BUILT_IN)
		ft_do_built_in_cmd(cmd);
	else if (cmd->type == BASIC)
		ft_do_basic_cmd(cmd);
	// close(cmd->infile);
	// close(cmd->outfile);
}

void	ft_do_pipe_cmd(t_cmd *cmd)
{
	int		outin[2];
	t_cmd	*current;

	pipe (outin);
	current = cmd;
	current->outfile = outin[1];
	ft_exec_pipe(current);
	current = current->next;
	while (current)
	{
		if (current->next)
		{
			current->infile = outin[0];
			current->outfile = outin[1];
			ft_exec_pipe(current);
		}
		else
		{
			current->infile = outin[0];
			ft_exec_pipe(current);
		}
		current = current->next;
	}
	close(outin[0]);
	close(outin[1]);
}
