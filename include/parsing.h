#ifndef PARSING_H
# define PARSING_H

/* For write and other else */
# include <unistd.h>

/* For malloc */
# include <stdlib.h>

typedef struct s_cmd
{
	char	**cmd;
	char	*type;
	s_cmd	*next;
}				t_cmd;

t_cmd	*ft_create_cmdlist(void);
int		ft_add_cmdelem(t_cmd *list, char **cmd, char *type);
int		ft_cmdlist_size(t_cmd *list);
void	ft_del_cmdlist(t_cmd *list);

#endif
