/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:12:16 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/07 11:38:14 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	ft_print_cmdlist(t_cmd *list)
{
	int	i;

	while (list != NULL)
	{
		ft_putendl_fd("---cmd---", 1);
		i = 0;
		while (list->cmd[i])
		{
			ft_putstr_fd(list->cmd[i], 1);
			i++;
		}
		printf("\ntype ->%d\ninfile->%d\noutfile->%d\n",
			list->type, list->infile, list->outfile);
		ft_putendl_fd("------", 1);
		list = list->next;
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
