/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utl2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:02:12 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/25 18:16:32 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	strj_the_var(char **env, char *v, int i)
{
	if (ft_strchr(env[i], '='))
			env[i] = ft_strjoin(env[i], v);
	else
	{
			env[i] = ft_strjoin(env[i], "=");
			env[i] = ft_strjoin(env[i], v);
	}
}

char	*ft_colect(char *s, char *c)
{
	char	*tmp;
	char	*col;

	tmp = ft_strjoin(s, "=");
	col = ft_strjoin(tmp, c);
	free(tmp);
	return (col);
}

void	add_to_env(char *name, char *value, char *f, char **env)
{
	int		i;
	int		j;
	char	**t;

	i = -1;
	while (env[++i])
	{
		t = ft_split(env[i], '=');
		if (!ft_strncmp(name, env[i], ft_strlen(t[0]))
			&& (ft_strlen(t[0]) == ft_strlen(name)))
		{
			j = 1;
			strj_the_var(env, value, i);
		}
		ft_free(t);
	}
	if (j != 1)
	{
		env[i] = ft_strdup(f);
		i++;
	}
	env[i] = NULL;
	return (free(value), free(name), free(f));
}

void	add_ne(char *arg, char **env)
{
	int		i;
	char	*name;
	char	*value;
	char	*f;
	int		j;

	i = 0;
	while (arg[i] != '+')
		i++;
	name = malloc(i + 1);
	i = -1;
	while (arg[++i] != '+')
		name[i] = arg[i];
	name[i] = '\0';
	value = malloc(ft_strlen(arg) - i + 1);
	j = 0;
	i++;
	if (arg[i] == '=')
		i++;
	while (arg[i])
		value[j++] = arg[i++];
	value[i] = '\0';
	f = ft_colect(name, value);
	add_to_env(name, value, f, env);
	return ;
}
