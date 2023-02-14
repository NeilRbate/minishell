#include "../../include/ms.h"

void	ft_env(void)
{
	t_env	*current;

	current = g_data.minishell_env;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	g_data.status_code = 0;
}
