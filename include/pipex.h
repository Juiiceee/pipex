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
	char	*cmd1;
	char	**argcmd1;
	char	*cmd2;
	char	**argcmd2;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

char	**ft_split(char const *s, char c);


#endif
