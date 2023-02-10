#include "../../include/parsing.h"

void	ft_print_lex(t_id *lex)
{
	while (lex != NULL)
	{
		ft_putstr_fd("type -> ", 1);
		ft_putnbr_fd(lex->type, 1);
		ft_putstr_fd(" index ->", 1);
		ft_putnbr_fd(lex->index, 1);
		ft_putstr_fd(" string-> |>", 1);
		ft_putstr_fd(lex->data, 1);
		ft_putstr_fd("<|", 1);
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
		return (ft_putendl_fd("error: malloc fail", 2), NULL);
	list->type = type;
	list->index = index;
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
	new->prev = list;
	list->next = new;
	return (0);
}
