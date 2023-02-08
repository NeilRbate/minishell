#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"

/* For write and other else */
# include <unistd.h>

/* For malloc */
# include <stdlib.h>

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
 *
*/

typedef struct	s_cmd
{
	char			**cmd;
	char			*type;
	char			*infile;
	char			*outfile;
	struct s_cmd	*next;
}				t_cmd;

typedef struct	s_id
{
	int				type;
	int				index;
	char			*data;
	struct	s_id	*next;
}				t_id;

/* ---- t_cmd TOOLS ---- */
t_cmd	*ft_create_cmdlist(char **cmd, char *type);
int		ft_add_cmdelem(t_cmd *list, char **cmd, char *type);
int		ft_cmdlist_size(t_cmd *list);
void	ft_del_cmdlist(t_cmd *list);
void	ft_print_cmdlist(t_cmd *list);

/* ---- t_id TOOLS ---- */
t_id	*ft_create_idlist(int type, int index, char *data);
int		ft_add_idelem(t_id *list, int type, int index, char *data);
int		ft_idlist_size(t_id *list);
void	ft_del_idlist(t_id *list);
void	ft_print_lex(t_id *lex);

/* ---- parsing parts ---- */
t_cmd	*ft_parsing(char *str);
void	ft_freesplit(char **split);

/* ---- lexic parts ---- */
t_id	*ft_lexical_analyse(char *str);
#endif
