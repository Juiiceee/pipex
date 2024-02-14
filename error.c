/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:57:18 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/14 10:43:52 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freetab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
		free(tab);
}

void	closefile(t_pipex *pipex)
{
	close(pipex->infile);
	close(pipex->outfile);
}

void	closepipe(t_pipex *pipex)
{
	close(pipex->pipe[0]);
	close(pipex->pipe[1]);
}

void	pexrror(char *str, t_pipex *pipex)
{
	if (pipex->infile < 0)
		pipex->infile = open("/dev/null", O_RDONLY);
	else if (pipex->pipe < 0)
	{
		perror(str);
		closefile(pipex);
		exit(1);
	}
	perror(str);
}

void	error(char *str, char *raison)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(raison, 2);
	ft_putstr_fd("\n", 2);
}
