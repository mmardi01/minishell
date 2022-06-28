/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mysplit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:41:21 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/04 14:33:48 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

int	ft_skip(char *str, char c)
{
	int	i;

	i = 1;
	while (str[i] != c)
		i++;
	return (i);
}

void	count(char *str, int *count)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && str[i] != ' ')
		{
			if (j == 0 && str[i] != '<' && str[i] != '>' && str[i] != '|')
			{
				(*count)++;
				j = 1;
			}
			if (str[i] == '"')
				i += ft_skip(&str[i], '"');
			else if (str[i] == '\'')
				i += ft_skip(&str[i], '\'');
			else if (str[i] == '<' || str[i] == '>' || str[i] == '|')
				i += ft_skip2(&str[i], count, &j);
			i++;
		}
		if (str[i] != '\0')
			i++;
	}
}

char	*get_word(char *str, int *j)
{
	char	*s;
	int		i;
	int		k;

	i = 0;
	k = -1;
	while (str[i] && str[i] != ' ' && str[i] != '<' \
		&& str[i] != '>' && str[i] != '|')
	{
		if (str[i] == '"')
			i += ft_skip(&str[i], '"');
		else if (str[i] == '\'')
			i += ft_skip(&str[i], '\'');
		i++;
	}
	s = malloc(sizeof(char) * i + 1);
	while (++k < i)
		s[k] = str[k];
	*j += i - 1;
	s[i] = '\0';
	return (s);
}

char	**split(char *str, int size)
{
	int		i;
	int		j;
	char	**s;

	s = malloc(sizeof(char *) * size + 1);
	i = 0;
	j = 0;
	s[size] = NULL;
	while (i < size)
	{
		if (str[j] != ' ')
		{
			if (str[j] == '>' || str[j] == '<' || str[j] == '|')
				s[i] = get_word2(&str[j], str[j], &j);
			else
				s[i] = get_word(&str[j], &j);
			i++;
		}
		j++;
	}
	return (s);
}

char	**mysplit(char *str)
{
	int		num;
	char	**s;

	num = 0;
	if (!str)
		return (NULL);
	count(str, &num);
	s = split(str, num);
	return (s);
}
