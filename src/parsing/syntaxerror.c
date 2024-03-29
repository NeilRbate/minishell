/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:20:08 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/31 16:23:32 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ms.h"

void	ft_putnlerror_fd(void)
{
	*g_data.status_code = 258;
	ft_puterror_fd("syntax error near unexpected token `newline'", 2);
}

void	ft_putperror_fd(void)
{
	*g_data.status_code = 258;
	ft_puterror_fd("syntax error near unexpected token `|'", 2);
}

void	ft_putpperror_fd(void)
{
	*g_data.status_code = 258;
	ft_puterror_fd("syntax error near unexpected token `||'", 2);
}

void	ft_putserror_fd(void)
{
	*g_data.status_code = 258;
	ft_puterror_fd("syntax error", 2);
}

int	ft_stxctrl(t_id *id)
{
	int	s;

	s = 0;
	while (id != NULL)
	{
		if (id->type == 0)
			s++;
		else if (id->type == 11)
		{
			id->type = 0;
			s++;
		}
		else if (id->type == 3 && s > 0)
			s = 0;
		else if ((id->next == NULL || id->type == 3) && s == 0)
			return (ft_putnlerror_fd(), -1);
		id = id->next;
	}
	if (s > 0)
		return (0);
	return (ft_putserror_fd(), -1);
}
