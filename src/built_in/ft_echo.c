/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:15:25 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/04 12:46:45 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms.h"

static int	ft_is_option(char *str, int *option)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	else
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			else
				*option += 1;
			i++;
		}
		return (1);
	}
}

void	ft_echo(t_cmd *cmdd)
{
	char	**cmd;
	int		i;
	int		option;

	cmd = cmdd->cmd;
	i = 1;
	option = 0;
	while (ft_is_option(cmd[i], &option))
		i++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], cmdd->outfile);
		if (cmd[i++ + 1])
			ft_putstr_fd(" ", cmdd->outfile);
	}
	if (option == 0)
		ft_putchar_fd('\n', cmdd->outfile);
	if (cmdd->outfile != 1)
		close(cmdd->outfile);
}
