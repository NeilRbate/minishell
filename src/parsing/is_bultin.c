#include "../../include/parsing.h"

void	ft_isbuiltin(t_cmd *id)
{
	while (id != NULL)
	{
		if (!ft_strncmp(id->cmd[0], "echo", 5))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "env", 4))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "exit", 5))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "export", 4))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "unset", 4))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "cd", 3))
			id->type = 1;
		else if (!ft_strncmp(id->cmd[0], "pwd", 4))
			id->type = 1;
		id = id->next;
	}
}
