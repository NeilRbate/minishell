#ifndef PARSING_H
# define PARSING_H
# include "../libft/libft.h"
/* For write and other else */
# include <unistd.h>
/* For malloc */
# include <stdlib.h>
# include <stdio.h>

/* ID_TYPE
 *
 * 0  ->  CHAR
 * 1  ->  '
 * 2  ->  "
 * 3  ->  |
 * 4  ->  \
 * 5  ->  \t, esp
 * 6  ->  \n
 * 7  ->  >
 * 8  ->  >>
 * 9  ->  <
 * 10 ->  <<
 * 11 -> $
 *
*/
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
/* ---- t_id TOOLS ---- */
t_id	*ft_create_idlist(int type, int index, char *data);
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
#endif
