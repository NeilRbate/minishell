#ifndef MS_EX_H
# define MS_EX_H

# include "parsing.h"
/* <unistd.h> included from libft */
/* <stdlib.h> included from libft */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>

# define PROMPT_MESS "minishell-1.0$ "

// Missing : cd, ctrl+ /, cmd pipe, code retour ($?)
/* SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL */
void	ft_sig_handle(int signal);
void	ft_new_command(void);
void	echo_ctl(int n);
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
int	ft_env_key_exist(char *key);

void	ft_export_var(char **var_lst);
#endif