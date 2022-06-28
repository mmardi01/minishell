/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:34:41 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/27 14:56:40 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_access(char *file, int flag)
{
	if (access(file, flag) != 0)
	{
		printf("minishell: permission denied: %s\n", file);
		return (0);
	}	
	return (1);
}

char	**only_commands(char **commands)
{
	char	**ocommands;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	ocommands = malloc(sizeof(char *) * 10);
	while (commands[i])
	{
		k = 0;
		if (commands[i][0] == '>' || commands[i][0] == '<')
		{
			k++;
			i++;
		}
		if (commands[i][0] != '>' && commands[i][0] != '<' && k == 0)
		{
			ocommands[j] = ft_strdup(commands[i]);
			j++;
		}
		i++;
	}
	ocommands[j] = 0;
	return (ocommands);
}

int	check_number(char **str, char c)
{
	int	i;

	i = 0;
	while (str[0][i] == c)
		i++;
	if (str[0][i] != '\0')
		return (4);
	if (!str[1])
		return (4);
	if (str[1][0] == '<' || str[1][0] == '>' || \
		str[1][0] == '|' || str[1][0] == ';')
		return (4);
	return (i);
}

int	check_redirections(char	**str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i][0] == '<')
		{
			get_glo_2(1);
			if (check_number(&str[i], str[i][0]) > 2)
				return (0);
		}
		else if (str[i][0] == '>')
		{
			get_glo_2(1);
			if (check_number(&str[i], str[i][0]) > 2)
				return (0);
		}
		else if (str[i][0] == '|')
		{
			get_glo_2(1);
			if (check_number(&str[i], str[i][0]) > 1)
				return (0);
		}
	}
	return (1);
}

int	check_permession(char **commands)
{
	int	i;

	i = -1;
	while (commands[++i])
	{
		if (commands[i][0] == '>')
		{
			if (access(commands[i + 1], F_OK) != 0)
				open(commands[i + 1], O_CREAT | O_RDWR, 0777);
			else if (!check_access(commands[i + 1], W_OK))
				return (0);
		}
		else if (commands[i][0] == '<' && commands[i][1] == '\0')
		{
			if (access(commands[i + 1], F_OK) != 0)
				return (printf ("minishell: no such file or dirtory: %s\n", \
				commands[i + 1]), 0);
			else if (!check_access(commands[i + 1], R_OK))
				return (0);
		}
	}
	return (1);
}
