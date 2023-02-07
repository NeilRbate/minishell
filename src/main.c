/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:31:56 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/07 12:23:06 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ms_ex.h"

int	main(void)
{
	signal(SIGINT, ft_sig_handle);
	while (1)
		ft_new_command();
	return (0);
}
