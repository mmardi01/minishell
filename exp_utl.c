/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:16:03 by mmardi            #+#    #+#             */
/*   Updated: 2022/07/07 12:51:54 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_name_var(char **env, char *arg)
{
	int		i;
	char	**t;
	int		j;

	j = 0;
	i = -1;
	while (env[++i])
	{
		t = ft_split(env[i], '=');
		if (!ft_strncmp(t[0], arg, ft_strlen(arg)) && \
		(ft_strlen(t[0]) == ft_strlen(arg)))
		{
			j = 1;
			return ;
		}
		ft_free(t);
	}
	if (j != 1)
	{
		env[i] = ft_strdup(arg);
		i++;
	}
	env[i] = NULL;
}

void	set_new_norm(char **env, char *name, char *f, int i)
{
	int		j;
	char	**t;

	while (env[++i])
	{
		t = ft_split(env[i], '=');
		if (!ft_strncmp(name, env[i], ft_strlen(t[0]))
			&& (ft_strlen(t[0]) == ft_strlen(name)))
		{
			j = 1;
			if (ft_strchr(f, '='))
			{
				free (env[i]);
				env[i] = ft_strdup (f);
			}
		}
		ft_free(t);
	}
	if (j != 1)
	{
		env[i] = ft_strdup (f);
		i++;
	}
	env[i] = NULL;
}

char	*final_srt(char *arg, char *name, int i)
{
	char	*value;
	char	*res;
	int		j;

	res = malloc(1);
	value = malloc(ft_strlen(arg) - i + 1);
	j = 0;
	if (arg[i] == '=')
		i++;
	while (arg[i])
	{
		value[j++] = arg[i++];
	}
	value[i] = '\0';
	res = ft_strjoin(res, name);
	if (ft_strchr(arg, '='))
		res = ft_strjoin(res, "=");
	if (value[0])
		res = ft_strjoin(res, value);
	free(value);
	return (res);
}

void	set_new_v(char *arg, char **env)
{
	int		i;
	char	*name;
	char	*res;

	i = 0;
	while (arg[i] != '=' && arg[i])
		i++;
	name = malloc(i + 1);
	i = -1;
	while (arg[++i] != '=' && arg[i])
		name[i] = arg[i];
	name[i] = '\0';
	res = final_srt(arg, name, i);
	set_new_norm(env, name, res, -1);
	free (res);
	free (name);
}

void	ft_exp_cmd(char *arg, char **env)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (arg[i] == '_' && arg[i + 1] == '=')
		return ;
	if (check_arg(arg))
	{
		g_status = 1;
		return ;
	}
	while (arg[j] && arg[j] != '+' && arg[j] != '=')
		j++;
	if (!(strchr(arg, '=')) && !(ft_strchr(arg, '+')))
		check_name_var(env, arg);
	else if (arg[j] == '+')
	{
		if (arg[j + 1] == '+' || arg[j + 1] == '=')
			add_ne(arg, env);
		return ;
	}
	else if (arg[j] == '=')
		set_new_v(arg, env);
}
