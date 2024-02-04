#include "../include/pipex.h"

int	parsingcommand(t_pipex *pipex, char **argv, int	nb)
{
	pipex->argcmd = ft_split(argv[nb], ' ');
	if (!pipex->argcmd)
		return (0);
	pipex->cmd = ft_strdup(pipex->argcmd[0]);
	if (!pipex->cmd)
		return (free(pipex->argcmd), 0);
	return (1);
}

void	addslash(t_pipex *pipex, char **env)
{
	int	i;

	i = 0;
	pipex->envpath = ft_split(pathenv(env), ':');
	if (!pipex->envpath)
		error("split");
	while (pipex->envpath[i])
	{
		pipex->envpath[i] = ft_strjoin(pipex->envpath[i], "/");
		if (!pipex->envpath[i])
			return (freetab(pipex->envpath), error("strjoin"));
		i++;
	}
}

char	*pathenv(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}
