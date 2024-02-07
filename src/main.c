/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:55:42 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/07 15:49:52 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
	pipex.pid0 = fork();
	if (pipex.pid0 == 0)
		process(pipex, argv, env, 0);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		process(pipex, argv, env, 1);
	closepipe(&pipex);
	waitpid(pipex.pid0, NULL, 0);
	waitpid(pipex.pid1, NULL, 0);
	closefile(&pipex);
	freetab(pipex.envpath);
	return (0);
}
