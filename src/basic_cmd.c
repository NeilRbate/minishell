#include "../include/minishell.h"

void	ft_do_basic(t_cmd *cmd)
{
	t_cmd	*cmd;
	pid_t	child;
	int		i;
	char    *command;

	i = 0;
	child = fork();
	if (child == 0)
	{
		while (data.cmd_path[i])
		{
			command = ft_strtrijoin(data.cmd_path[i], "/", cmd->cmd[0]);
			if (access(command, F_OK) == 0)
				if (execve(command, cmd->cmd, envpa->envp) == -1)
					ft_cmd_error(cmd->cmd[0]);
			free(command);
			i++;
		}
		ft_cmd_error(cmd->cmd[0]);
	}
	waitpid(child, 0, 0);
}
