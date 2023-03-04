#include "../include/ms.h"

static int	ft_is_option(char *str, int *option)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	else
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			else
				*option += 1;
			i++;
		}
		return (1);
	}
}

void	ft_echo(t_cmd *cmdd)
{
	char	**cmd;
	int		i;
	pid_t	child;
	int		option;

	child = fork();
	if (child == 0)
	{
		dup2(cmdd->outfile, 1);
		cmd = cmdd->cmd;
		i = 1;
		option = 0;
		while (ft_is_option(cmd[i], &option))
			i++;
		while (cmd[i])
		{
			ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
		if (option == 0)
			ft_putchar_fd('\n', 1);
		exit(0);
	}
	waitpid(child, g_data.status_code, 0);
}
