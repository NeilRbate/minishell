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
		if (id->type == 11 && type == 2 && id->next->type == 0)
		{
			ft_putendl_fd("INTERPRETER LE $$$",2);
			id = id->next;
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

int	ft_endctrl(t_id *id)
{
	while (id->next != NULL)
		id = id->next;
	if ((id->type >= 0 && id->type <= 2)
		|| (id->type >= 5 && id->type <= 6) || id->type == 11)
		return (0);
	return (ft_putendl_fd("error: invalid syntax", 2), -1);
}

int	ft_idctrl(t_id *id)
{
	int	i;

	i = 0;
	if (id->type == 5 || id->type == 6)
		while ((id->type == 5 || id->type == 6) && id)
			id = id->next;
	if (id->type == 3)
		return (ft_putendl_fd("error: invalid syntax", 2), -1);
	while (id != NULL)
	{
		if (id->type == 3 && id->next->type == 3 && id->next != NULL)
			return (ft_putendl_fd("error: invalid syntax", 2), -1);
		if (id->type == 1 || id->type == 2)
		{
			i = ft_quotectrl(id, id->type);
			if (i < 0)
				return (-1);
			while (i != id->index && id->next != NULL)
				id = id->next;
			if (id->next == NULL)
				return (0);
		}
		else
			id = id->next;
			ft_putendl_fd("\ncoucou\n", 2);
	}
	return (0);
}

int	ft_syntax_analyse(t_id *lex)
{
	if (ft_idctrl(lex) != 0)
		return (-1);
	if (ft_endctrl(lex) != 0)
		return (-1);
	return (0);
}
