/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:23:45 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/27 15:43:08 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**dupplic(char **env)
{
	char	**str;
	int		len;
	int		i;

	len = 0;
	while (env[len])
		len++;
	str = malloc(sizeof(char *) * len + 1);
	if (!str)
		return (0);
	i = -1;
	while (env[++i])
		str[i] = ft_strdup(env[i]);
	str[i] = NULL;
	return (str);
}

void	ft_aficher(char **str, int i, int fd)
{
	int	y;
	int	j;
	int	l;

	y = 0;
	l = 0;
	while (str[++i])
	{
		write(fd, "declare -x ", 11);
		j = 0;
		y = 0;
		while (str[i][j])
		{
			write(fd, &str[i][j], 1);
			if (str[i][j] == '=' && y == 0)
			{
				y = 1;
				write(fd, "\"", 1);
			}
			j++;
		}
		if (y == 1)
			write(fd, "\"", 1);
		write(fd, "\n", 1);
	}
}

void	display(char **env, int fd)
{
	char	**str;
	int		i;
	int		y;
	char	*temp;

	str = dupplic(env);
	i = -1;
	while (str[++i])
	{
		y = i + 1;
		while (str[y])
		{
			if (ft_strcmp(str[i], str[y]) > 0)
			{
				temp = str[y];
				str[y] = str[i];
				str[i] = temp;
			}
			y++;
		}
	}
	i = -1;
	ft_aficher(str, i, fd);
	ft_free(str);
}

int	ft_export(char **cmd, char **env, int fd)
{
	int		i;

	i = 1;
	g_status = 0;
	if (!cmd[i])
		display(env, fd);
	else
	{
		while (cmd[i])
			ft_exp_cmd(cmd[i++], env);
	}
	return (1);
}
