#include "../../include/parsing.h"

t_id	*ft_quote_ctrl(t_id *id)
{
	if (id->type == 1)
	{
		id = id->next;
		while (id->type != 1 && id != NULL)
		{
			id->type = 0;
			id = id->next; 
			if (id == NULL)
				return (ft_putendl_fd("error: invalid syntax", 2), NULL);
		}
		return (id);
	}
	if (id->type == 2)
		return (id);
	return (NULL);
}

t_id	*ft_id_ctrl(t_id *id)
{
	while (id != NULL)
	{
		if (id->type == 1 || id->type == 2)
		{
			id = ft_quote_ctrl(id);
			if (!id)
				return (NULL);
		}
		id = id->next;
	}
	return (id);
}

t_cmd	*ft_syntax_analyse(t_id *lex)
{
	t_cmd	*ret;
	t_id	*stock;

	ret = NULL;
	stock = ft_id_ctrl(lex);
	if (!stock)
		ft_del_idlist(lex);
	ft_putendl_fd("?|?|?| AFTER CUT ?|?|?|?", 1);
	ft_print_lex(lex);
	return (ret);
}
