#include "../include/parsing.c"

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

void	ft_del_cmdlist(t_cmd *list)
{
	t_cmd	*stock;
	
	if (ft_list_size(list) == 1)
		free(list);
	stock = list;
	while (list->next != NULL)
	{
		free(stock);
		stock = list;
		list = list->next;
	}
	free(stock);
}

int	ft_add_cmdelem(t_cmd *list, char **cmd, char *type)
{
	t_cmd	*stock;

	while (list->next != NULL)
		list = list->next;
	stock = malloc(sizeof(*stock));
	if (!stock)
		return (ft_putendl_fd("error: malloc fail", 2), 1);
	list->next = stock;
	stock->cmd = cmd;
	stock->type = type;
	return (0);
}

t_cmd	*ft_create_cmdlist(void)
{
	t_cmd	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (ft_putendl_fd("error: malloc fail", 2), NULL);
	list->cmd = NULL;
	list->type = NULL;
	list->next = NULL;
	return (list);
}
