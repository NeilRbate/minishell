#include "../include/parsing.h"

int	main(int argc, char **argv)
{
	t_cmd	*ret;
	if (argc < 2)
		return (ft_putendl_fd("Too few arguments !\n", 2), 2);
	ret = ft_parsing(argv[1]);
	ft_print_cmdlist(ret);
	ft_del_cmdlist(ret);
	return (0);
}
