#include "../../include/ms.h"

static int	ft_check_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_error_unset(char *str)
{
	char	*err;
	char	*tmp;

	err = ft_strjoin("minishell: unset: '", str);
	tmp = ft_strjoin(err, "': not a valid identifier");
	ft_putendl_fd(tmp, 2);
	free(err);
	free(tmp);
}

void	ft_unset(t_cmd *command)
{
	pid_t	child;
	char	**keys;
	char	*key;
	int		i;

	child = fork();
	if (child == 0)
	{
		keys = command->cmd;
		i = 0;
		while (keys[++i])
		{
			key = ft_strjoin(keys[i], "=");
			if (ft_check_key(keys[i]) == 0)
			{
				if (ft_env_key_exist(keys[i]))
					ft_del_env_element(keys[i]);
			}
			else
				ft_error_unset(keys[i]);
			free(key);
		}
		exit(0);
	}
	waitpid(child, 0, 0);
}
