#include "../include/pipex.h"

int	parsingcommand(t_pipex *pipex, char **argv, int	nb)
{
	char	*tmp;

	pipex->argcmd = ft_split(argv[nb], ' ');
	if (access(pipex->argcmd[0], X_OK))
	{
		while (*pipex->envpath)
		{
			tmp = ft_strjoin(*pipex->envpath, "/");
			pipex->cmd = ft_strjoin(tmp, pipex->argcmd[0]);
			free(tmp);
			if (!access(pipex->cmd, X_OK))
				return (1);
			free(pipex->cmd);
			pipex->envpath++;
		}
		return (0);
	}
	pipex->cmd = ft_strdup(pipex->argcmd[0]);
	return (1);
}

char	*pathenv(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	closepro(t_pipex *pipex, int nb)
{
	closefile(pipex);
	closepipe(pipex);
	if (nb == 0)
	{
		error(pipex->argcmd[0], "command not found");
		freetab(pipex->argcmd);
	}
	else
	{
		error(pipex->argcmd[0], "command fail");
		freetab(pipex->argcmd);
	}
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
			closepro(&pipex, 0);
		if (execve(pipex.cmd, pipex.argcmd, env) == -1)
			closepro(&pipex, 1);
	}
	else
	{
		dup2(pipex.pipe[0], 0);
		close(pipex.pipe[1]);
		dup2(pipex.outfile, 1);
		if (parsingcommand(&pipex, argv, 3) == 0)
			closepro(&pipex, 1);
		if (execve(pipex.cmd, pipex.argcmd, env) == -1)
			closepro(&pipex, 1);
	}
}
