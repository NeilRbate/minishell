// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   unset.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/02/09 11:09:36 by efirmino          #+#    #+#             */
// /*   Updated: 2023/02/09 12:41:00 by efirmino         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../include/minishell.h"

// static int	ft_valid_unset(char *str)
// {
// 	int	i;
// }

// void	ft_unset(t_cmd *command)
// {
// 	pid_t	child;
// 	t_cmd	*current;
// 	char	*key;
// 	t_env	*current;

// 	child = fork();
// 	if (child == 0)
// 	{
// 		current = command;
// 		key = current->cmd[1];
// 		if (!ft_valid_unset(key))
// 		{
// 			ft_err_msg(current->cmd[0], current->cmd[1], "not a valid identifier");
// 			return ;
// 		}
// 	}
// 	waitpid(child, 0, 0);
// }
