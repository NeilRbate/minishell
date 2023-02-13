#include "../../include/ms.h"

void	ft_env(void)
{
	pid_t	child;
	int		i;
	char	**env;

	child = fork();
	if (child == 0)
	{
		env = g_data.minishell_env;
		i = 0;
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
		g_data.status_code = 0;
		exit(0);
	}
	waitpid(child, 0, 0);
}
