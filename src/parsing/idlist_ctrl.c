#include "../../include/parsing.h"

int	ft_quotectrl(t_id *id, int type)
{
	if (id->next == NULL)
		return (ft_putendl_fd("error: invalid syntax", 2), -1);
	if (id->next->type == type)
		return (id->next->index);
	id = id->next;
	while (id->next != NULL)
	{
		if (type == 2 && id->type == 11)
		{
			if (id->next->type == 0)
				id = id->next->next;
			else
				return (ft_putendl_fd("error: invalid syntax", 2), -1);
		}
		else
		{
			id->type = 0;
			id = id->next;
		}
		if (id->type == type)
			return (id->index);
	}
	if (id->type != 1)
		return (ft_putendl_fd("error: invalid syntax", 2), -1);
	return (id->index);
}

int	ft_idctrl(t_id *id)
{
	int	i;

	i = 0;
	while (id != NULL)
	{
		if (id->type == 1 || id->type == 2)
		{
			i = ft_quotectrl(id, id->type);
			if (i < 0)
				return (-1);
			while (i != id->index)
				id = id->next;
			if (id->next == NULL)
				return (0);
			id = id->next;
		}
		else
			id = id->next;
	}
	return (0);
}

t_cmd	*ft_syntax_analyse(t_id *lex)
{
	t_cmd	*ret;

	ret = NULL;
	if (ft_idctrl(lex) != 0)
		return (ft_del_idlist(lex), NULL);
	return (ret);
}
