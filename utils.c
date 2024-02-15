/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbehr <lbehr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:57:34 by lbehr             #+#    #+#             */
/*   Updated: 2024/02/14 11:58:52 by lbehr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		write(fd, &*s, 1);
		s++;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*chaine;
	size_t	len;
	int		i;
	int		t;

	i = 0;
	t = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	chaine = malloc(len + 1);
	if (!chaine)
		return (NULL);
	while (s1[i])
	{
		chaine[i] = s1[i];
		i++;
	}
	while (s2[t])
	{
		chaine[i + t] = s2[t];
		t++;
	}
	chaine[i + t] = '\0';
	return (chaine);
}

char	*ft_strdup(char *src)
{
	char	*new;
	int		nb;
	int		i;

	i = 0;
	nb = ft_strlen(src);
	new = (char *)malloc((nb + 1) * sizeof(char));
	if (new == 0)
		return (new);
	while (src[i] != '\0')
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s2)
		return (-1);
	while ((*s1 || *s2) && (n > 0))
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
