#include "../../include/parsing.h"

t_cmd	*ft_cmdlist(t_id *id)
{
	//Cette fonction BUG, a FIX et c'est fini !!!
	t_id	*stock;
	t_cmd	*ret;
	char	**cmd;
	int	i;

	ret = NULL;
	while (id != NULL)
	{
		i = 0;
		while (id->type != 3 && id->next != NULL)
		{
			i++;
			id = id->next;
		}
		cmd = malloc(sizeof(char) * i + 1);
		if (!cmd)
			return (ft_putendl_fd("error: malloc fail", 2), NULL);
		cmd[i] = NULL;
		if (id->type == 3)
			stock = id->prev;
		else
			stock = id;
		while (i > 0)
		{
			i--;
			cmd[i] = ft_strdup(stock->data);
			stock = stock->prev;
		}
		if (ret == NULL)
			ret = ft_create_cmdlist(cmd, NULL);
		else
			ft_add_cmdelem(ret, cmd, NULL);
		if (id->next == NULL)
			return (ret);
		id = id->next;
	}
	return (ret);
}

t_id	*ft_clean_id(t_id *id)
{
	t_id	*stock;

	while (id->type != 0 && id != NULL)
	{
		stock = id;
		id = id->next;
		ft_del_idelem(stock);
	}
	stock = id;
	if (stock == NULL || stock->next == NULL)
		return (stock);
	while (id != NULL)
	{
		if (id->type == 0 || id->type == 3)
			id = id->next;
		else
		{
			if (id->next != NULL)
			{
				id = id->next;
				ft_del_idelem(id->prev);
			}
			else
			{
				if (id->type != 0)
				{
					id->prev->next = NULL;
					ft_del_idelem(id);
				}
				id = NULL;
			}
		}
	}
	return (stock);
}

t_cmd	*ft_parsing(char *str)
{
	t_id	*lex;
	t_cmd	*cmd;

	if (str[0] == '\0')
		return (ft_putendl_fd("error: invalid syntax", 2), NULL);
	lex = ft_lexical_analyse(str);
	if (!lex)
		return (NULL);
	if (ft_syntax_analyse(lex) != 0)
		return (ft_del_idlist(lex), NULL);
	lex = ft_clean_id(lex);
	cmd = ft_cmdlist(lex);
	if (!cmd)
		return (ft_del_idlist(lex), NULL);
	ft_del_idlist(lex);
	ft_print_cmdlist(cmd);
//	ft_del_cmdlist(cmd);
	return (cmd);
}
