#include "../include/pipex.h"

void	closepro(t_pipex *pipex)
{
	closefile(pipex);
	error(pipex->argcmd[0], "command not found");
	freetab(pipex->argcmd);
	exit(0);
}

void	process(t_pipex pipex, char **argv, char **env, int nb)
{
	if (nb == 0)
	{
		dup2(pipex.pipe[1], 1);
		close(pipex.pipe[0]);
		dup2(pipex.infile, 0);
		if (parsingcommand(&pipex, argv, 2) == 0)
			closepro(&pipex);
		execve(pipex.cmd, pipex.argcmd, env);
	}
	else
	{
		dup2(pipex.pipe[0], 0);
		close(pipex.pipe[1]);
		dup2(pipex.outfile, 1);
		if (parsingcommand(&pipex, argv, 3) == 0)
			closepro(&pipex);
		execve(pipex.cmd, pipex.argcmd, env);
	}
}
