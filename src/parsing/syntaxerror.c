/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxerror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 10:20:08 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/09 14:21:19 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

int	ft_stxctrl(t_id *id)
{
	int	s;

	s = 0;
	while (id != NULL)
	{
		if (id->type == 0)
			s++;
		else if (id->type == 3 && s > 0)
			s = 0;
		else if ((id->next == NULL || id->type == 3) && s == 0)
			return (ft_puterror_fd("invalid syntax", 2), -1);
		id = id->next;
	}
	if (s > 0)
		return (0);
	return (ft_puterror_fd("invalid syntax", 2), -1);
}
