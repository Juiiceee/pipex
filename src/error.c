#include "../include/pipex.h"

void	pexrror(char *str, t_pipex *pipex)
{
	if (pipex->infile < 0)
		;
	else if (pipex->outfile < 0)
		close(pipex->infile);
	else if (pipex->pipe < 0)
		closefile(pipex);
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

