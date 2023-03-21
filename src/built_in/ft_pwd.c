/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:16:22 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/21 11:54:19 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_pwd(t_cmd *command)
{
	char	*str;

	str = getcwd(0, 1000);
	ft_putendl_fd(str, command->outfile);
	ft_env_add("PWD", str);
	free(str);
	*g_data.status_code = 0;
}
