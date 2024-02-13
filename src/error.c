/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:57:18 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/13 10:10:41 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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
		;
	else if (pipex->outfile < 0)
		close(pipex->infile);
	else if (pipex->pipe < 0)
		closefile(pipex);
	perror(str);
	exit(0);
}

void	error(char *str, char *raison)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(raison, 2);
	ft_putstr_fd("\n", 2);
}
