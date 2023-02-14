#include "../../include/ms.h"

static void	ft_export_no_args(void)
{
	t_env	*current;

	current = g_data.minishell_env;
	while (current)
	{
		printf("declare -x %s=%c%s%c\n", current->key, '"', current->value, '"');
		current = current->next;
	}
	g_data.status_code = 0;
}

static void	ft_export_error_message(char *keyval)
{
	char	*tmp;
	char	*tmpp;

	tmp = ft_strjoin("minishell: export: `", keyval);
	tmpp = ft_strjoin(tmp, "': not a valid identifier");
	free(tmp);
	ft_putendl_fd(tmpp, 2);
	free(tmpp);
	g_data.status_code = 1;
}

static int	ft_export_valid_key(char *key, char	*keyval)
{
	int		i;
	char	*str;

	str = key;
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_export_error_message(keyval);
			g_data.status_code = 1;
			return (0);
		}
		i++;
	}
	return (1);
}

static void	ft_export_args(char **to_export)
{
	char	**list;
	int		i;
	char	*key;
	char	*value;
	int		j;

	i = 0;
	list = to_export;
	while (list[i])
	{
		j = 0;
		while (list[i][j] && list[i][j] != '=')
			j++;
		key = ft_substr(list[i], 0, j);
		value = ft_strdup(list[i] + j + 1);
		if (ft_export_valid_key(key, list[i]))
		{
			ft_env_add(key, value);
			g_data.status_code = 0;
		}
		free(key);
		free(value);
		i++;
	}
}

void	ft_export(t_cmd *command)
{
	char	**export;

	export = command->cmd;
	if (!export[1])
		ft_export_no_args();
	else
		ft_export_args(export + 1);
}
