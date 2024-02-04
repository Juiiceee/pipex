#include "../include/pipex.h"

void	pexrror(char *str)
{
	perror(str);
	exit(0);
}

void	error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

