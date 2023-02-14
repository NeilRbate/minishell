#include "../../include/ms.h"

void	ft_pwd(void)
{
	pid_t	child;
	t_env	*current;

	child = fork();
	if (child == 0)
	{
		current = g_data.minishell_env;
		while (current)
		{
			if (!ft_strncmp(current->key, "PWD", 4))
			{
				printf("%s\n", current->value);
			}
			current = current->next;
		}
		g_data.status_code = 0;
		exit(0);
	}
	waitpid(child, 0, 0);
}
