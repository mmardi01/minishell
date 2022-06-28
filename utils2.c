/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:54:21 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/23 16:44:49 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	ft_clt_d(void)
{
	write(1, CTL_D, 13);
	exit (0);
}

int	ft_check_exit(char **s)
{
	if (!s[0])
		return (1);
	if (ft_strcmp(s[0], "exit") == 0 && !s[1])
	{
		write (1, "exit\n", 5);
		exit (0);
	}	
	else if (ft_strcmp(s[0], "exit") == 0 && s[1])
	{
		printf ("exit: too many arguments\n");
		return (0);
	}
	return (1);
}

int	ft_skip2(char *str, int *count, int *j)
{
	int	i;

	i = 0;
	(*j) = 1;
	if (str[i] == '<')
		while (str[i] == '<')
			i++;
	else if (str[i] == '>')
		while (str[i] == '>')
			i++;
	else if (str[i] == '|')
		while (str[i] == '|')
			i++;
	i--;
	(*count)++;
	if (str[i + 1] != ' ' && str[i + 1] != '\0')
		(*count)++;
	return (i);
}

char	*get_word2(char *str, char c, int *j)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i] == c)
		i++;
	s = malloc(sizeof(char) * i + 1);
	(*j) += i - 1;
	i = 0;
	while (str[i] == c)
	{
		s[i] = str[i];
		i++;
	}
	return (s);
}
