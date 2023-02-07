#include "../include.parsing.c"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (ft_putstr("Too few arguments !\n"));
	ft_parsing(argv[2]);
	return (0);
}
