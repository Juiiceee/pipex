#include "../include/pipex.h"

void	pexrror(char *str)
{
	perror(str);
	exit(0);
}

void	error(char *str, char *raison)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(raison, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
}

