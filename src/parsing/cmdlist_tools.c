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
			ft_putendl_fd(list->cmd[i], 1);
			i++;
		}
		ft_putendl_fd("--Type--", 1);
		ft_putnbr_fd(list->type, 1);
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

int	ft_add_cmdelem(t_cmd *list, char **cmd, int type)
{
	t_cmd	*stock;

	stock = ft_create_cmdlist(cmd, type);
	if (!stock)
		return (-1);
	while (list->next != NULL)
		list = list->next;
	list->next = stock;
	return (0);
}

t_cmd	*ft_create_cmdlist(char **cmd, int type)
{
	t_cmd	*list;

	list = malloc(sizeof(*list));
	if (!list)
		return (ft_putendl_fd("error: malloc fail", 2), NULL);
	list->cmd = cmd;
	list->type = type;
	list->next = NULL;
	return (list);
}
