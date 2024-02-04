#include "../include/pipex.h"

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	//char	*argv[] = {"sa", "coucou", "ls", "cc"};
	//char *str[] = {"coucou", "/bin/ls -l"};
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		pexrror("open infile");
	pipex.outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0640);
	if (pipex.outfile < 0)
		pexrror("open outfile");
	if (pipe(pipex.pipe) == -1)
		pexrror("pipe");
	addslash(&pipex, env);
	pipex.pid0 = fork();
	if (pipex.pid0 == 0)
		fprocess(pipex, argv, env);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		sprocess(pipex, argv, env);
	waitpid(pipex.pid0, NULL, 0);
	waitpid(pipex.pid1, NULL, 0);
	freetab(pipex.envpath);
	//free(pipex.argcmd);
	//free(pipex.argcmd2);
	//free(pipex.cmd);
	//free(pipex.cmd2);
	//lib(&pipex);
	return 0;
}
