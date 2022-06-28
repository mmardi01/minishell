/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 21:50:59 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/28 20:50:41 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*bitween_dollars(char *s, int *j)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != '$' && ft_is_alphanum(s[i]))
		i++;
	str = malloc(sizeof(char) * i + 1);
	i = 0;
	while (s[i] && s[i] != '$' && ft_is_alphanum(s[i]))
	{
		str[i] = s[i];
		i++;
	}
	*j += i;
	str[i] = '\0';
	return (str);
}

char	*bitween_dollars2(char *s, int *j)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != '$')
		i++;
	str = malloc(sizeof(char) * i + 1);
	i = 0;
	while (s[i] && s[i] != '$')
	{
		str[i] = s[i];
		i++;
	}
	*j += i - 1;
	str[i] = '\0';
	return (str);
}

char	*get_value(char *str)
{
	int		i;
	char	*s;

	i = -1;
	s = NULL;
	while (str[++i])
	{
		if (str[i] == '$' && ft_is_alphanum(str[i + 1]))
			s = ft_strjoin(s, getenv(bitween_dollars(&str[i + 1], &i)));
		else if (str[i] == '$' && str[i + 1] == '?')
		{
			s = ft_strjoin(s, ft_itoa(g_status));
			i++;
		}
		else
		{
			if (str[i] == '$')
			{
				s = ft_strjoin(s, "$");
				i++;
			}
			s = ft_strjoin(s, bitween_dollars2(&str[i], &i));
		}
	}
	return (s);
}

void	handledollar(char **s, int *tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (ft_strchr(s[i], '$') && !tab[i])
		{
			if (s[i - 1] && s[i - 1][0] != '<')
				s[i] = get_value(s[i]);
		}
		i++;
	}
}
