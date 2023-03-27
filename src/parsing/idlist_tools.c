/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idlist_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:15:29 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/27 15:22:00 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parsing.h"

void	ft_print_lex(t_id *lex)
{
	while (lex != NULL)
	{
		printf("lex->prev->%p\nlex->%p\nlex->next->%p\n",
			lex->prev, lex, lex->next);
		ft_putstr_fd("type -> ", 1);
		ft_putnbr_fd(lex->type, 1);
		ft_putstr_fd(" index ->", 1);
		ft_putnbr_fd(lex->index, 1);
		ft_putstr_fd(" string-> |>", 1);
		ft_putstr_fd(lex->data, 1);
		ft_putstr_fd("<| infile ->", 1);
		ft_putnbr_fd(lex->infile, 1);
		ft_putstr_fd(" outfilefile ->", 1);
		ft_putnbr_fd(lex->outfile, 1);
		ft_putendl_fd("", 1);
		lex = lex->next;
	}
}

int	ft_idlist_size(t_id *list)
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

t_id	*ft_create_idlist(int type, int index, char *data)
{
	t_id	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (ft_puterror_fd("malloc fail", 2), NULL);
	list->type = type;
	list->index = index;
	list->infile = 0;
	list->outfile = 1;
	list->data = data;
	list->next = NULL;
	list->prev = NULL;
	return (list);
}

int	ft_add_idelem(t_id *list, int type, int index, char *data)
{
	t_id	*new;

	new = ft_create_idlist(type, index, data);
	if (!new)
		return (-1);
	while (list->next != NULL)
		list = list->next;
	list->infile = 0;
	list->outfile = 1;
	new->prev = list;
	list->next = new;
	return (0);
}

void	ft_del_idelem(t_id *id)
{
	t_id	*next;
	t_id	*prev;

	if (id->next == NULL && id->prev != NULL)
	{
		prev = id->prev;
		free(id->data);
		free(id);
		id = id->prev;
		id->next = NULL;
	}
	else if (id->next == NULL && id->prev == NULL)
		ft_del_idlist(id);
	else
	{
		next = id->next;
		prev = id->prev;
		free(id->data);
		free(id);
		if (next)
			next->prev = prev;
		if (prev)
			prev->next = next;
	}
}
