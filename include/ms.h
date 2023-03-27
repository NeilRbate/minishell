/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:15:51 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/27 16:46:10 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# include "parsing.h"
# define PROMPT_MESS "minishell-5.7$ "

# define BASIC 0
# define BUILT_IN 1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_big
{
	t_cmd			*cmds;
	t_env			*minishell_env;
	char			**exec_env;
	char			**cmd_path;
	int				*status_code;
}	t_big;

t_big	g_data;

/* SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL */
void	ft_sig_handle(int signal);
void	ft_sig_handle_nothing(int sig);
void	ft_new_command(void);
void	echo_ctl(int n);
void	ft_sig_handle_doubleshell(int sig);
/* COMMAND EXECUTION - COMMAND EXECUTION - COMMAND EXECUTION */
void	ft_do_basic_cmd(t_cmd *cmd);
void	ft_do_built_in_cmd(t_cmd *cmd);
void	ft_do_pipe_cmd(t_cmd *cmd);
char	*ft_check_access(char *to_test);
void	ft_check_slash(char *str);
/* BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN */
void	ft_echo(t_cmd *cmdd);
void	ft_env(t_cmd *command);
void	ft_exit(t_cmd *command);
void	ft_pwd(t_cmd *command);
void	ft_cd(t_cmd *command);
void	ft_export(t_cmd *command);
void	ft_unset(t_cmd *command);
/* UTILS - UTILS - UTILS - UTILS - UTILS - UTILS - UTILS - UTILS - UTILS */
void	ft_env_setup(char **envp);
int		ft_env_key_exist(char *key);
void	ft_env_add(char *key, char *value);
void	ft_env_del(char	*key);
void	ft_env_replace(char *key, char *value);
void	ft_set_env_for_exec(void);
char	*ft_get_env_value(char *key);
char	*ft_strtrijoin(char const *s1, char const *s2, char const *s3);
void	ft_error_msg(char *command);
void	ft_free_global(void);
void	ft_wait_all_pids(t_cmd *mds);
void	ft_free_cmd(t_cmd *cmd);
void	ft_path_setup(void);
void	ft_export_error_message(char *keyval);
/* FREE - FREE - FREE - FREE - FREE - FREE - FREE - FREE - FREE - FREE - FREE */
void	ft_free_split(char **tab);
void	ft_free_t_env(void);

#endif
