/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:24:22 by mmardi            #+#    #+#             */
/*   Updated: 2022/07/07 12:59:32 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_arg2(char *cmd)
{
	int	i;
	int	a;
	int	p;

	p = 0;
	a = 0;
	i = 0;
	if (!ft_is_alpha(cmd[0]))
	{
		printf("minishell: unset: %s: invalid option\n", cmd);
		return (1);
	}
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_is_alphanum(cmd[i]))
		{
			if (cmd[i] == '+' && cmd[i + 1] == '=')
				break ;
			printf("minishell: unset: %s: invalid option\n", cmd);
			return (1);
		}
		i++;
	}
	return (0);
}

int	count2(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		i++;
	}
	return (i);
}

int	remove_from_env_utils(char **env, char *arg, int l, int *i)
{
	int		j;

	*i = -1;
	while (env[++(*i)])
	{
		j = (*i) + 1;
		if (ft_strncmp(arg, env[*i], count2(env[*i])) == 0
			&& (count2(env[*i]) == ft_strlen(arg)))
		{
			free (env[*i]);
			l = 1;
			while (env[j])
				env[(*i)++] = env[j++];
		}
	}
	return (l);
}

void	remove_from_env(char *arg, char **env, int l)
{
	int	i;

	if (check_arg2(arg))
		return ;
	l = remove_from_env_utils(env, arg, l, &i);
	if (l)
	{
		env[i - 1] = NULL;
	}
}

int	ft_unset(char **arg, char **env)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		remove_from_env(arg[i], env, 0);
	}
	return (1);
}
