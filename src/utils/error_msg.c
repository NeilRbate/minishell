/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 08:45:54 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/20 11:52:53 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_error_msg(char *command)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	*g_data.status_code = 127;
}

void	ft_export_error_message(char *keyval)
{

	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(keyval, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	*g_data.status_code = 1;
}
