#include "../include/pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, &*s, 1);
		s++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*chaine;
	size_t	len;
	int		i;
	int		t;

	i = 0;
	t = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	chaine = malloc(len + 1);
	if (!chaine)
		return (NULL);
	while (s1[i])
	{
		chaine[i] = s1[i];
		i++;
	}
	while (s2[t])
	{
		chaine[i + t] = s2[t];
		t++;
	}
	chaine[i + t] = '\0';
	return (chaine);
}

char	*ft_strdup(char *src)
{
	char	*new;
	int		nb;
	int		i;

	i = 0;
	nb = ft_strlen(src);
	new = (char *)malloc((nb + 1) * sizeof(char));
	if (new == 0)
		return (new);
	while (src[i] != '\0')
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && (n > 0))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

/*int	checkarg(int argc)
{
	if (argc != 5)
	{
		error("")
	}
}*/

int	checkbin(char *str)
{
	char	*bin;
	int		i;

	i = 0;
	bin = ft_strdup("/bin/");
	if (!str || !bin)
		return (-1);
	while (str[i])
	{
		if (bin[i] != str[i])
			break ;
		i++;
	}
	if (i == 5)
		return (free(bin), 0);
	return (free(bin), 1);
}

/*void	checkcom(t_pipex *pipex, char **argv)
{
	int	i;

	i = 0;
	if (access(pipex->cmd, X_OK) == -1)
	{
		while (pipex->envpath[i])
		{
			if (access(ft_strjoin(pipex->envpath[i])))
			i++;
		}
	}
	if (access(pipex->cmd2, X_OK) == -1)
		pexrror("access");
}*/

char	*pathenv(char **env)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

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

/*void	lib(t_pipex *pipex)
{
	freetab(pipex->envpath);
	free(pipex->argcmd);
	printf("pipex->argcmd = %s\n", pipex->argcmd);
	free(pipex->argcmd2);
	printf("pipex->argcmd = %s\n", pipex->argcmd);
	free(pipex->cmd);
	printf("pipex->argcmd = %s\n", pipex->argcmd);
	free(pipex->cmd2);
	printf("pipex->argcmd = %s\n", pipex->argcmd);
}*/

int	parsingcommand(t_pipex *pipex, char **argv, int	nb)
{
	pipex->argcmd = ft_split(argv[nb], ' ');
	if (!pipex->argcmd)
		return (0);
	pipex->cmd = ft_strdup(pipex->argcmd[0]);
	if (!pipex->cmd)
		return (free(pipex->argcmd), 0);
	if (!pipex->argcmd)
		return (0);
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

void	fprocess(t_pipex pipex, char **argv, char **env)
{
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[0]);
	dup2(pipex.pipe[1], 1);
	if (parsingcommand(&pipex, argv, 3) == 0)
		return ;
	execve(pipex.cmd, pipex.argcmd, env);
}

int main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	//char	*argv[] = {"sa", "coucou", "ls", "cc"};
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		pexrror("open infile");
	pipex.outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0640);
	if (pipex.outfile < 0)
		pexrror("open outfile");
	if (pipe(pipex.pipe) == -1)
		pexrror("pipe");
	addslash(&pipex, env);
	while (*pipex.envpath)
	{
		printf("%s\n",*pipex.envpath);
		pipex.envpath++;
	}
	//checkcom(&pipex, argv);
	/*if (execve(pipex.cmd, argv + 1, env) == -1)
		perror("execve");*/

	/*pipex.pid1 = fork();
	if (pipex.pid1 == 0)
	{
		fprocess(pipex, argv, env);
	}*/
	parsingcommand(&pipex, argv, 2);
	freetab(pipex.envpath);
	//free(pipex.argcmd);
	//free(pipex.argcmd2);
	//free(pipex.cmd);
	//free(pipex.cmd2);
	//lib(&pipex);
	return 0;
}
