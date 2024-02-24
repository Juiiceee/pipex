/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:57:44 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/24 11:27:34 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fprocess(t_pipex pipex, char **argv, char **env)
{
	if ((int)ft_strlen(argv[2]) == 0 || argv[2][0] == ' ')
	{		
		closefile(&pipex);
		closepipe(&pipex);
		freetab(pipex.envpath);
		error(" ", "Command not found");
		exit (127);
	}
	dup2(pipex.pipe[1], 1);
	close(pipex.pipe[0]);
	dup2(pipex.infile, 0);
	if (parsingcommand(&pipex, argv, 2) == 0)
	{
		freetab(pipex.envpath);
		closepro(&pipex, 0);
	}
	if (execve(pipex.cmd, pipex.argcmd, env) == -1)
		closepro(&pipex, 1);
}

void	sprocess(t_pipex pipex, char **argv, char **env)
{
	if (pipex.outfile < 0)
	{
		freetab(pipex.envpath);
		exit (1);
	}
	if ((int)ft_strlen(argv[3]) == 0 || argv[3][0] == ' ')
	{
		closefile(&pipex);
		closepipe(&pipex);
		freetab(pipex.envpath);
		error(" ", "Command not found");
		exit (127);
	} 
	dup2(pipex.pipe[0], 0);
	close(pipex.pipe[1]);
	dup2(pipex.outfile, 1);
	if (parsingcommand(&pipex, argv, 3) == 0)
	{
		freetab(pipex.envpath);
		closepro(&pipex, 0);
	}
	if (execve(pipex.cmd, pipex.argcmd, env) == -1)
		closepro(&pipex, 1);
}
