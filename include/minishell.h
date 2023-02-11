#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "ms_ex.h"
# include "parsing.h"

# define BASIC 0
# define BUILT_IN 1
# define PIPE 2

typedef struct s_big
{
	struct s_env	*minishell_env;
	char			**cmd_path;
	int				status_code; // $?
	t_cmd			*cmds;
}	t_big;

t_big	data;

#endif