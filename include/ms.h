/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 09:15:51 by efirmino          #+#    #+#             */
/*   Updated: 2023/03/06 13:49:32 by efirmino         ###   ########.fr       */
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
# define PROMPT_MESS "minishell-1.1$ "

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
void	ft_new_command(void);
/* COMMAND EXECUTION - COMMAND EXECUTION - COMMAND EXECUTION */
void	ft_do_basic_cmd(t_cmd *cmd);
void	ft_do_built_in_cmd(t_cmd *cmd);
void	ft_do_pipe_cmd(t_cmd *cmd);
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
/* FREE - FREE - FREE - FREE - FREE - FREE - FREE - FREE - FREE - FREE - FREE */
void	ft_free_split(char **tab);
void	ft_free_t_env(void);

#endif


// void	ft_print_cmdlist(t_cmd *list)
// {
// 	int	i;

// 	while (list != NULL)
// 	{
// 		i = 0;
// 		while (list->cmd[i])
// 		{
// 			ft_putstr_fd(list->cmd[i], 1);
// 			ft_putchar_fd(' ', 1);
// 			i++;
// 		}
// 		printf("infile: %d\noutfile: %d", list->infile, list->outfile);
// 		list = list->next;
// 		printf("\n - - - \n");
// 	}
// }