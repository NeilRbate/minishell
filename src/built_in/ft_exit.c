#include "../../include/ms.h"

void	ft_exit(void)
{
	if (g_data.status_code)
		free(g_data.status_code);
	if (g_data.minishell_env)
		ft_free_t_env();
	if (g_data.cmd_path)
		ft_free_split(g_data.cmd_path);
	system("leaks minishell");
	exit(0);
}
