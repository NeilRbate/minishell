#include "../../include/ms.h"

static void	ft_cd_error_msg(char *str)
{
	char	*tmp;

	tmp = ft_strdup("minishell: cd: ");
	ft_putstr_fd(tmp, 2);
	perror(str);
	free(tmp);
}

static void	ft_go_to(char *to_go, char *old_pwd)
{
	char	*new_pwd;

	if (access(to_go, F_OK) == -1)
	{
		ft_cd_error_msg(to_go);
		*g_data.status_code = 1;
		return ;
	}
	chdir(to_go);
	new_pwd = getcwd(0, 100);
	ft_env_add("OLDPWD", old_pwd);
	ft_env_add("PWD", new_pwd);
	free(new_pwd);
	*g_data.status_code = 0;
}

static void	ft_go_home(char *old_pwd)
{
	char	*home;

	if (ft_env_key_exist("HOME") == 0)
	{
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		*g_data.status_code = 1;
		return ;
	}
	home = ft_get_env_value("HOME");
	ft_go_to(home, old_pwd);
	free(home);
}

void	ft_cd(t_cmd *cmd)
{
	char	*old_pwd;
	char	*to_go;

	to_go = cmd->cmd[1];
	old_pwd = ft_get_env_value("PWD");
	if (to_go == 0)
		ft_go_home(old_pwd);
	else
		ft_go_to(to_go, old_pwd);
	free(old_pwd);
}	
