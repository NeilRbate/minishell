#include "../../include/ms.h"

void	ft_exit(void)
{
	ft_free_t_env();
	ft_free_split(g_data.cmd_path);
	system("leaks minishell");
	exit(0);
}
