#include "../../include/parsing.h"

t_cmd	*ft_split_args(char **args)
{
	t_cmd	*ret;
	char	**split;
	int		i;

	i = 1;
	ret = ft_create_cmdlist(ft_split(args[0], 32), NULL);
	if (!ret)
		return (NULL);
	while (args[i])
	{
		split = ft_split(args[i], 32);
		ft_add_cmdelem(ret, split, NULL);
		i++;
	}
	return (ret);
}

t_cmd	*temp_pars(char *str)
{
	t_cmd	*ret;
	char	**args;

	if (ft_strchr(str, '|') == NULL)
		return (ft_create_cmdlist(ft_split(str, 32), NULL));
	args = ft_split(str, '|');
	ret = ft_split_args(args);
	ft_freesplit(args);
	return (ret);
}

t_cmd	*ft_parsing(char *str)
{
	t_id	*lex;

	lex = ft_lexical_analyse(str);
	if (!lex)
		return (NULL);
	return (temp_pars(str));
}
