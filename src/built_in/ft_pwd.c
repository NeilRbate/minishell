#include "../../include/ms.h"

void	ft_pwd(void)
{
	char	**env;
	int		i;
	pid_t	child;

	child = fork();
	if (child == 0)
	{
		env = g_data.minishell_env;
		i = 0;
		while (env[i])
		{
			if (!ft_strncmp("PWD=", env[i], 4))
			{
				printf("%s\n", env[i] + 4);
				g_data.status_code = 0;
				exit(0);
			}
			i++;
		}
		g_data.status_code = 0;
		exit(0);
	}
	waitpid(child, 0, 0);
}
