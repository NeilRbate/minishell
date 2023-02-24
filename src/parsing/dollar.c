#include "../../include/ms.h"

void	ft_convertdoll(t_id *id, t_env *env)
{
	while (env != NULL)
		{
			if(ft_strncmp(id->data, env->key,
				ft_strlen(env->key)) == 0)
			{
				free(id->data);
				id->data = ft_strdup(env->value);
						break;
			}
			else
				env = env->next;
		}
	if (env == NULL)
	{
		free(id->data);
		id->data = ft_strdup("");
	}
		free(id->prev->data);
		id->prev->data = ft_strdup("");
		id->prev->type = 0;
}
void	ft_doll(t_id *id)
{
	t_env	*env;

	env = g_data.minishell_env;
	if (ft_strncmp(id->data, "?", 1) == 0)
	{
		free(id->data);
		id->data = ft_itoa(*g_data.status_code);
		free(id->prev->data);
		id->prev->data = ft_strdup("");
		id->prev->type = 0;
	}
	else
		ft_convertdoll(id, env);
}
