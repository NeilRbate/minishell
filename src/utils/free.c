#include "../../include/ms.h"

void	ft_free_split(char **tab)
{
	char	**tmp;
	int		i;

	tmp = tab;
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp[i]);
	free(tmp);
}
