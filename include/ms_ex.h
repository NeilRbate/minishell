/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:15:28 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/09 14:43:35 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EX_H
# define MS_EX_H

# define PROMPT_MESS "minishell-1.0$ "

# include "parsing.h"
# include "../libft/libft.h"
/* <unistd.h> included from libft */
/* <stdlib.h> included from libft */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_big
{
	struct s_env	*minishell_env;
	int		status_code; // $?
	t_cmd	*cmds;
}	t_big;

t_big	data;

/* SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL */
void	ft_sig_handle(int signal);
void	ft_new_command(void);

/* BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN */
void	ft_echo(t_cmd *command);
void	ft_env(void);
void	ft_exit(void);

/* UTILS - UTILS - UTILS - UTILS - UTILS - UTILS - UTILS - UTILS - UTILS */
void	ft_get_env(char **envp);
void	ft_add_element(char *key, char *value, t_env **minishell_env);
void	ft_err_msg(char *cmd, char *arg, char *msg);

// void	ft_free_env(char **env);

#endif