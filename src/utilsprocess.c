/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilsprocess.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 10:31:44 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/13 12:15:59 by lbehr            ###   ########.fr       */
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
		while (pipex->envpath[i])
		{
			tmp = ft_strjoin(pipex->envpath[i], "/");
			if (!tmp)
				return (0);
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
	while (ft_strncmp("PATH", *env, 4))
		env++;
	return (*env + 5);
}

void	closepro(t_pipex *pipex, int nb)
{
	closefile(pipex);
	closepipe(pipex);
	if (nb == 0)
	{
		error(pipex->argcmd[0], "command not found");
		freetab(pipex->argcmd);
	}
	else
	{
		error(pipex->argcmd[0], "command fail");
		freetab(pipex->argcmd);
	}
	exit(0);
}
