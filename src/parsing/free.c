#include "../../include/parsing.h"

void	ft_del_idlist(t_id *list)
{
	t_id	*stock;

	while (list != NULL)
	{
		stock = list->next;
		if (list->data != NULL)
			free(list->data);
		free(list);
		list = stock;
	}
}

void	ft_del_cmdlist(t_cmd *list)
{
	t_cmd	*stock;

	while (list != NULL)
	{
		stock = list->next;
		if (list->cmd != NULL)
			ft_freesplit(list->cmd);
		if (list->type != NULL)
			free(list->type);
		free(list);
		list = stock;
	}
}

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
}
