#include "../include/pipex.h"

void	fprocess(t_pipex pipex, char **argv, char **env)
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[0]);
	dup2(pipex.pipe[1], 1);
	if (parsingcommand(&pipex, argv, 3) == 0)
		return ;
	execve(pipex.cmd, pipex.argcmd, env);
}

