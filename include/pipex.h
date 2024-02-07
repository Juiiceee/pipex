#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>

typedef	struct s_pipex
{
	int		outfile;
	int		infile;
	int		pipe[2];
	char	**envpath;
	char	*cmd;
	char	**argcmd;
	pid_t	pid0;
	pid_t	pid1;
}	t_pipex;

//ft_split.c
char	**ft_split(char const *s, char c);

//process.c
void	process(t_pipex pipex, char **argv, char **env, int nb);
int		parsingcommand(t_pipex *pipex, char **argv, int	nb);
char	*pathenv(char **env);

//error.c
void	error(char *str, char *raison);
void	pexrror(char *str, t_pipex *pipex);
void	closepipe(t_pipex *pipex);
void	freetab(char **tab);
void	closefile(t_pipex *pipex);

//utils.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(char *src);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);

#endif
