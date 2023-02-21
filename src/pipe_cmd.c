/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 08:48:38 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/18 09:02:02 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

void	ft_pipe_to_out(t_cmd *cmd, int tmp_fd);

void	ft_do_pipe_cmd(t_cmd *cmd)
{
	int		tmp_fd;
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		// if (current->next)
		// 	ft_pipe_for_next(current, tmp_fd);
		// else
			ft_pipe_to_out(current, tmp_fd);
		current = current->next;
	}
}

void	ft_pipe_to_out(t_cmd *cmd, int tmp_fd)
{
	
}
