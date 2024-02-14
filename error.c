/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:57:18 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/14 13:34:45 by lbehr            ###   ########.fr       */
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
	char	*tmp1;
	char	*tmp2;
	char	*tmpgen;

	tmp1 = ft_strjoin(str, ": ");
	tmp2 = ft_strjoin(raison, "\n");
	tmpgen = ft_strjoin(tmp1, tmp2);
	write(2, tmpgen, ft_strlen(tmpgen));
	free(tmp1);
	free(tmp2);
	free(tmpgen);
}
