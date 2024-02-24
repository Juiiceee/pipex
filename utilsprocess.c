/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsprocess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:31:44 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/24 11:23:05 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parsingcommand(t_pipex *pipex, char **argv, int nb)
{
	char	*tmp;
	int		i;

	i = 0;
	if (ft_strlen(argv[nb]) == 0)
		return (0);
	pipex->argcmd = ft_split(argv[nb], ' ');
	if (access(pipex->argcmd[0], X_OK))
	{ 
		if (!pipex->envpath)
			return (0);
		while (pipex->envpath[i])
		{
			tmp = ft_strjoin(pipex->envpath[i], "/");
			pipex->cmd = ft_strjoin(tmp, pipex->argcmd[0]);
			free(tmp);
			if (!access(pipex->cmd, X_OK))
				return (1);
			free(pipex->cmd);
			i++;
		}
		return (0);
	}
	pipex->cmd = ft_strdup(pipex->argcmd[0]);
	return (1);
}

char	*pathenv(char **env)
{
	int	check;

	check = 1;
	if (!env)
		return (NULL);
	while (check && *env)
	{
		env++;
		check = ft_strncmp("PATH", *env, 4);
	}
	if (check == 0)
		return (*env + 5);
	return (NULL);
}

void	closepro(t_pipex *pipex, int nb)
{
	closefile(pipex);
	closepipe(pipex);
	if (nb == 0)
	{
		error(pipex->argcmd[0], "Command not found");
		freetab(pipex->argcmd);
	}
	else
	{
		error(pipex->argcmd[0], "Command fail");
		freetab(pipex->argcmd);
	}
	exit(127);
}
