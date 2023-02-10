/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 10:00:08 by efirmino          #+#    #+#             */
/*   Updated: 2023/02/10 10:02:05 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "ms_ex.h"
# include "parsing.h"

# define BASIC 0;
# define BUILT_IN 1;
# define PIPE 2;

typedef struct s_big
{
	struct s_env	*minishell_env;
	int				status_code; // $?
	t_cmd			*cmds;
}	t_big;

t_big	data;

#endif