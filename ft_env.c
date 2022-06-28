/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 21:23:37 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/28 18:47:17 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shlvl_increm(char **env, int i)
{
	char	*tmp;
	int		k;
	char	*t;
	char	*s;

	tmp = "SHLVL=";
	t = ft_strrchr(env[i], '=');
	k = ft_atoi(++t) + 1;
	s = ft_itoa(k);
	tmp = ft_strjoin(tmp, s);
	free (s);
	env[i] = ft_strdup(tmp);
	get_globale(1);
	free (tmp);
}

int	ft_check(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (!ft_strncmp("SHLVL=", env[i], 6))
			return (1);
	return (0);
}

int	ft_env(char **env)
{
	int	i;

	i = 0;
	if (ft_check(env))
	{
		while (env[i])
		{
			if (!ft_strncmp("SHLVL=", env[i], 6))
			{
				shlvl_increm(env, i);
				i++;
			}
			env[i] = ft_strdup(env[i]);
			i++;
		}
		env[i] = 0;
	}
	else
	{
		while (env[i])
			i++;
		env[i] = ft_strdup("SHLVL=1");
		env[i + 1] = 0;
	}
	return (1);
}

int	ft_print_env(char **env, int fd)
{
	int	i;

	i = -1;
	g_status = 0;
	while (env[++i])
	{
		if (ft_strchr(env[i], '='))
		{
			ft_putstr_fd(env[i], fd);
			ft_putstr_fd("\n", fd);
		}
	}
	return (1);
}
