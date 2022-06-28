/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:40:14 by mmardi            #+#    #+#             */
/*   Updated: 2021/11/12 12:08:32 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	count_words(const char *str, char c)
{
	int	i;
	int	t;

	t = 0;
	i = 0;
	while (*str)
	{
		if (*str != c && t == 0)
		{
			i++;
			t++;
		}
		else if (*str == c)
			t = 0;
		str++;
	}
	return (i);
}

static char	*word_dup(const char *str, int start, int end)
{
	int		i;
	char	*s;

	i = 0;
	s = malloc((end - start + 1) * sizeof(char));
	while (start < end)
	{
		s[i] = str[start];
		i++;
		start++;
	}
	s[i] = '\0';
	return (s);
}

static char	**freeing(char **tab, int j)
{
	while (j >= 0)
		free(tab[j--]);
	return (NULL);
}

static char	**ft_split2(char **split, const char *s, char c)
{
	int	i;
	int	j;
	int	index;

	j = 0;
	i = 0;
	index = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
			if (!split)
			{
				return (freeing(split, j));
			}
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

char	**ft_split(const char *s, char c)
{
	char	**p;

	if (!s)
		return (NULL);
	p = malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!p)
		return (NULL);
	ft_split2(p, s, c);
	return (p);
}
