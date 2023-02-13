#ifndef MS_H
# define MS_H

# include "../libft/libft.h"
/* <unistd.h> included from libft */
/* <stdlib.h> included from libft */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>

# define PROMPT_MESS "minishell-1.0$ "

# define BASIC 0
# define BUILT_IN 1
# define PIPE 2

typedef struct s_cmd
{
	char	**cmd;
	int		type;
	int		infile;
	int		outfile;
}	t_cmd;

typedef struct s_big
{
	t_cmd			*cmds;
	char			**minishell_env;
	char			**cmd_path;
	int				status_code;
}	t_big;

t_big	g_data;

/* SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL */
void	ft_sig_handle(int signal);
void	ft_new_command(void);
void	ft_do_basic(t_cmd *cmd);
void	ft_do_built_in(t_cmd *cmd);
void	ft_do_pipe(t_cmd *cmd);
/* BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN */
void	ft_echo(t_cmd *cmdd);
void	ft_env(void);
void	ft_exit(void);
void	ft_pwd(void);
void	ft_cd(t_cmd *command);
void	ft_export(t_cmd *command);
void	ft_unset(t_cmd *command);
/* UTILS - UTILS - UTILS - UTILS - UTILS - UTILS - UTILS - UTILS - UTILS */
void	ft_get_env(char **envp);
void	ft_add_env_element(char *key, char *value);
void	ft_del_env_element(char *key);
void	ft_free_split(char **tab);
int		ft_env_key_exist(char *key);
void	ft_export_var(char **var_lst);

#endif