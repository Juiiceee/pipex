/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:55:42 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/13 10:41:48 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static	void	ft_end(t_pipex *pipex)
{
	closepipe(pipex);
	waitpid(pipex->pid0, NULL, 0);
	waitpid(pipex->pid1, NULL, 0);
	closefile(pipex);
	freetab(pipex->envpath);
}

int	main(int argc, char *argv[], char *env[])
{
	t_pipex	pipex;

	if (argc != 5)
		return (0);
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		pexrror("open infile", &pipex);
	pipex.outfile = open(argv[4], O_TRUNC | O_CREAT | O_RDWR, 0644);
	if (pipex.outfile < 0)
		pexrror("open outfile", &pipex);
	if (pipe(pipex.pipe) < 0)
		pexrror("pipe", &pipex);
	pipex.envpath = ft_split(pathenv(env), ':');
	if (!pipex.envpath)
		closefile(&pipex);
	pipex.pid0 = fork();
	if (pipex.pid0 == 0)
		fprocess(pipex, argv, env);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		sprocess(pipex, argv, env);
	ft_end(&pipex);
	return (0);
}
