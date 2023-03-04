/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:17 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/04 09:16:17 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

// static int	ft_check_args(char **strs)
// {
// 	int	i;

// 	i = 0;
// 	while (strs[1][i])
// 	{
// 		if (!ft_isdigit(strs[1][i]))
// 		{
// 			//
// 		}
// 	}
// }

void	ft_exit(t_cmd *command)
{
	(void)command;
	exit(0);
}
