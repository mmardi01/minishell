/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:37:24 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/27 22:47:50 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_number(char *str)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == '"')
		{
			count++;
			i++;
			while (str[i] && str[i] != '"')
				i++;
		}
		else if (str[i] == '\'')
		{
			count++;
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '"' || str[i] == '\'')
			count++;
	}
	return (count % 2);
}

char	*remove_quotes(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[j])
	{	
		while (str[j] == '"')
		{
			j++;
			while (str[j] != '"')
				str[i++] = str[j++];
			j++;
		}
		while (str[j] == '\'')
		{
			j++;
			while (str[j] != '\'')
				str[i++] = str[j++];
			j++;
		}	
		str[i++] = str[j++];
	}
	str[i] = '\0';
	return (str);
}

int	*handle_quotes(char **s)
{
	int	i;
	int	*tab;

	i = 0;
	while (s[i])
		i++;
	tab = malloc(sizeof(int) * i);
	i = 0;
	while (s[i])
	{
		if (s[i][0] == '\'')
			tab[i] = 1;
		else
			tab[i] = 0;
		s[i] = remove_quotes(s[i]);
		i++;
	}
	return (tab);
}

void	handle_commands(char *str, char **env)
{
	char	**s;
	int		*tab;

	s = mysplit(str);
	tab = handle_quotes(s);
	handledollar(s, tab);
	if (!check_redirections(s))
	{
		g_status = 258;
		printf ("minishell: syntax error\n");
	}
	else if (get_glo_2(4) == 1)
		executable(s, env);
	else
	{
		if (ft_check_command(s, env, 1) == 0)
			if (executable(s, env) == 0)
				printf("minishell: %s: command not found\n", s[0]);
	}
	ft_free(s);
}
