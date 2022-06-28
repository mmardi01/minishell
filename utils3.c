/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:44:43 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/23 15:10:08 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *str)
{
	char	*s;

	s = malloc(ft_strlen(str) + 1 * sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, str, ft_strlen(str) + 1);
	return (s);
}

char	**cmd_btw_pipes(char **str)
{
	char	**commands;
	int		i;

	i = 0;
	while (str[i] && str[i][0] != '|')
		i++;
	commands = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (str[i] && str[i][0] != '|')
	{
		commands[i] = ft_strdup(str[i]);
		i++;
	}
	commands[i] = NULL;
	return (commands);
}

int	get_fd2(char **commands)
{
	int		i;
	char	*str;
	int		fd;

	i = 0;
	fd = 0;
	if (commands[i][0] == '<' && commands[i][1] == '\0')
		fd = open(commands[i + 1], O_CREAT | O_RDWR);
	else if (commands[i][0] == '<' && commands[i][1] == '<')
	{
		fd = open("../.a", O_CREAT | O_RDWR, 0777);
		while (1)
		{
			str = readline("> ");
			if (!str || ft_strcmp(str, commands[i + 1]) == 0)
				break ;
			write (fd, str, ft_strlen(str));
			write(fd, "\n", 1);
		}
		close(fd);
		fd = open("../.a", O_RDWR, 0777);
	}
	return (fd);
}
