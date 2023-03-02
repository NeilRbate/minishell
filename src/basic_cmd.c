#include "../include/ms.h"

static char	*ft_strtrijoin(char const *s1, char const *s2, char const *s3)
{
	int		i;
	int		j;
	char	*str;
	int		len;

	i = 0;
	j = 0;
	if (!(s1) || !(s2))
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	str = malloc(sizeof(char) * len + 1);
	if (!(str))
		return (0);
	while (s1[i])
			str[j++] = s1[i++];
	i = 0;
	while (s2[i])
			str[j++] = s2[i++];
	i = 0;
	while (s3[i])
			str[j++] = s3[i++];
	str[j] = '\0';
	return (str);
}

void	ft_do_basic_cmd(t_cmd *cmd)
{
	pid_t	child;
	int		i;
	char	*command;

	i = 0;
	child = fork();
	if (child == 0)
	{
		dup2(0, cmd->infile);
		dup2(1, cmd->outfile);
			while (g_data.cmd_path[i])
		{
			command = ft_strtrijoin(g_data.cmd_path[i], "/", cmd->cmd[0]);
			if (access(command, F_OK) == 0)
				if (execve(command, cmd->cmd, g_data.exec_env) == -1)
					perror("minishell: ");
					//error code
			free(command);
			i++;
		}
		close(cmd->infile);
		close(cmd->outfile);
		exit(0);
		perror("minishell: ");
		//error code
	}
	waitpid(child, g_data.status_code, 0);
}
