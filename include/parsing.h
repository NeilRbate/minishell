/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbarbate <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:21:24 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/02 09:30:00 by jbarbate         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../libft/libft.h"

/* For write and other else */
# include <unistd.h>
/* For malloc & printf */
# include <stdlib.h>
# include <stdio.h>
/* For open etc */
# include <fcntl.h>

typedef struct	s_cmd
{
	char			**cmd;
	int			type;
	int			infile;
	int			outfile;
	struct s_cmd	*next;
}				t_cmd;
typedef struct	s_id
{
	int		type;
	int		index;
	int		infile;
	int		outfile;
	char		*data;
	struct	s_id	*next;
	struct	s_id	*prev;
}				t_id;
/* ---- t_cmd TOOLS ---- */
t_cmd	*ft_create_cmdlist(char **cmd, int type, int infile, int outfile);
int		ft_add_cmdelem(t_cmd *list, char **cmd, int infile, int outfile);
int		ft_cmdlist_size(t_cmd *list);
void	ft_del_cmdlist(t_cmd *list);
void	ft_print_cmdlist(t_cmd *list);
void	ft_isbuiltin(t_cmd *id);
/* ---- t_id TOOLS ---- */
t_id	*ft_create_idlist(int type, int index, char *data);
void	ft_doll(t_id *id);
int		ft_add_idelem(t_id *list, int type, int index, char *data);
int		ft_idlist_size(t_id *list);
int		ft_del_oneid(t_id *id);
void	ft_del_idlist(t_id *list);
void	ft_del_idelem(t_id *id);
void	ft_print_lex(t_id *lex);
/* ---- parsing parts ---- */
t_cmd	*ft_parsing(char *str);
void	ft_freesplit(char **split);
/* ---- lexic parts ---- */
t_id	*ft_lexical_analyse(char *str);
int		ft_syntax_analyse(t_id *lex);
/* ---- redir parts ---- */
int		ft_redirctrl(t_id *id);
int		ft_openredir(char *file, int type, t_id *id);
int		ft_writepipe(char *str);
int		ft_heredoc(t_id *id);
char	*ft_gstrjoin(char *s1, char *s2);
int		ft_openread(char *file);
#endif
