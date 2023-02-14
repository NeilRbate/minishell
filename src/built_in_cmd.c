#include "../include/ms.h"

void	ft_do_built_in_cmd(t_cmd *command)
{
	char	*str;

	str = command->cmd[0];
	if (!ft_strncmp(str, "echo", 5))
		ft_echo(command);
	else if (!ft_strncmp(str, "env", 4))
		ft_env();
	else if (!ft_strncmp(str, "exit", 5))
		ft_exit();
	else if (!ft_strncmp(str, "export", 4))
		ft_export(command);
	else if (!ft_strncmp(str, "unset", 4))
		ft_unset(command);
	// else if (!ft_strncmp(str, "cd", 3))
	// 	ft_cd(command);
	else if (!ft_strncmp(str, "pwd", 4))
		ft_pwd();
}
