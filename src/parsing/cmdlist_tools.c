/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:12:16 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/06 13:51:51 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	ft_print_cmdlist(t_cmd *list)
{
	int	i;

	printf("- - - \n");
	while (list != NULL)
	{
		i = 0;
		while (list->cmd[i])
		{
			ft_putendl_fd(list->cmd[i], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
		printf("infile: %d\noutfile: %d", list->infile, list->outfile);
		list = list->next;
		printf("\n - - - \n");
	}
}

int	ft_cmdlist_size(t_cmd	*list)
{
	int	i;

	i = 1;
	while (list->next != NULL)
	{
		list = list->next;
		i++;
	}
	return (i);
}

int	ft_add_cmdelem(t_cmd *list, char **cmd, int infile, int outfile)
{
	t_cmd	*stock;

	stock = ft_create_cmdlist(cmd, 0, infile, outfile);
	if (!stock)
		return (-1);
	while (list->next != NULL)
		list = list->next;
	list->next = stock;
	return (0);
}

t_cmd	*ft_create_cmdlist(char **cmd, int type, int infile, int outfile)
{
	t_cmd	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (ft_puterror_fd("malloc fail", 2), NULL);
	list->cmd = cmd;
	list->type = type;
	list->infile = infile;
	list->outfile = outfile;
	list->next = NULL;
	return (list);
}
