/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:21:24 by jbarbate          #+#    #+#             */
/*   Updated: 2023/03/21 12:57:31 by efirmino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../libft/libft.h"
/* For malloc & printf */
# include <stdio.h>
/* For open etc */
# include <fcntl.h>

typedef struct s_cmd
{
	char			**cmd;
	int				type;
	pid_t			pid;
	int				pipe[2];
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}				t_cmd;
typedef struct s_id
{
	int				type;
	int				index;
	int				infile;
	int				outfile;
	char			*data;
	struct s_id		*next;
	struct s_id		*prev;
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
t_id	*ft_dollctrl(t_id *id, int *i);
t_id	*ft_joindoll(t_id *id);
int		ft_add_idelem(t_id *list, int type, int index, char *data);
int		ft_idlist_size(t_id *list);
int		ft_del_oneid(t_id *id);
char	**ft_splitstr(char *str, char *charset);
int	ft_containchar(t_id *id);
void	ft_del_idlist(t_id *list);
void	ft_doll(t_id *id);
void	ft_del_idelem(t_id *id);
void	ft_print_lex(t_id *lex);
void	ft_cleanidws(t_id *id);
/* ---- parsing parts ---- */
t_cmd	*ft_parsing(char *str);
void	ft_puterror_fd(char *str, int fd);
void	ft_freesplit(char **split);
int		ft_stxctrl(t_id *id);
int		ft_returnempty(t_id *id);
/* ---- lexic parts ---- */
t_id	*ft_lexical_analyse(char *str);
int		ft_syntax_analyse(t_id *lex);
/* ---- redir parts ---- */
int		ft_redirctrl(t_id *id);
int		ft_openredir(char *file, int type);
char	*ft_retd(int i, int j, char *str);
char	*ft_cutheredocdoll(char *stock);
char	*ft_heredocdoll(char *str);
char	*ft_splitdoll(char *str, char *doll, char *doll_i);
char	*ft_gstrjoin(char *s1, char *s2);
char	*ft_strndup(char *str, int size);
int		ft_heredocstr(t_id *id);
int		ft_openread(char *file);
t_id	*ft_heredoc(t_id *id, t_id *stock);
t_id	*ft_firstinfile(t_id *id);
t_id	*ft_multiinfile2(t_id *id, t_id *s);
t_id	*ft_endredir(t_id *id);
t_id	*ft_multioutfile2(t_id * id, t_id *stock);
t_id	*ft_lastoutfile(t_id * id, t_id *stock);
#endif
