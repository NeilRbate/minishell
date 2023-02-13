/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 09:58:40 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/13 13:25:58 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	ft_go_home(void)
// {
	
// }

void	ft_cd(t_cmd *command)
{
	char	**strs;
	pid_t	child;
	char	c[100];
	char	*str;

	child = fork();
	if (child == 0)
	{
		strs = command->cmd;
		if (strs[1] == 0)
		{
			printf("go home \n");
			// ft_go_home();
		}
		else
		{
			if (access(strs[1], F_OK) == 0)
				perror("minishell: cd: ");
			chdir(strs[1]);
			str = getcwd(c, 100);
			printf("%s\n", c);
		}
	}
	waitpid(child, 0, 0);
}
