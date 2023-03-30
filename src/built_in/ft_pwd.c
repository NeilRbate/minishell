/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:22 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/30 14:06:45 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_pwd(t_cmd *command)
{
	char	*str;

	str = ft_get_env_value("PWD");
	if (str == 0)
	{
		str = getcwd(0, 1000);
		ft_putendl_fd(str, command->outfile);
		ft_env_add("PWD", str);
		free(str);
		*g_data.status_code = 0;
	}
	else
	{
		ft_putendl_fd(str, command->outfile);
		free(str);
		*g_data.status_code = 0;
	}
}
