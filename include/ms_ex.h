/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_ex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 08:15:28 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/07 13:02:02 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EX_H
# define MS_EX_H

# define PROMPT_MESS "minishell-1.0$ "

# include "../libft/libft.h"
/* <unistd.h> included from libft */
/* <stdlib.h> included from libft */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>


/* SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL - SIGNAL */
void	ft_sig_handle(int signal);
void	ft_new_command(void);

/* BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN - BUILT-IN */
void	ft_echo(char **arg, int infile, int outfile);

#endif