/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 14:14:22 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/27 15:41:17 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(char	**env, char *pwd, char *oldpwd)
{
	int	i;
	int	k;
	int	j;

	i = -1;
	j = 0;
	k = 0;
	while (env[++i])
	{
		if (ft_strncmp("PWD", env[i], 3) == 0)
		{
			j++;
			env[i] = ft_strjoin("PWD=", pwd);
		}
		if (ft_strncmp("OLDPWD", env[i], 6) == 0)
		{
			k++;
			env[i] = ft_strjoin("OLDPWD=", oldpwd);
		}
	}
	if (!k)
		env[i++] = ft_strjoin("OLDPWD=", oldpwd);
	if (!j)
		env[i++] = ft_strjoin("PWD=", pwd);
	env[i] = 0;
}

char	*get_env(char *str, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
			return (&env[i][ft_strlen(str)]);
	}
	return (NULL);
}

int	ft_cd(char **line, char **env)
{
	char	oldpwd[10000];
	char	pwd[10000];

	getcwd(oldpwd, sizeof(oldpwd));
	g_status = 1;
	if (!line[1] && chdir(get_env("HOME=", env)) == -1)
		return (printf("minishell: cd: Home not set\n"), 1);
	else if (line[1] && line[1][0] == '-')
	{
		if (chdir(get_env("OLDPWD=", env)) == -1)
			return (printf("minishell: cd: OLDPWD not set\n"), 1);
		else
			printf("%s\n", get_env("OLDPWD=", env));
	}	
	else if (line[1] && chdir(line[1]) == -1)
		return (printf("minishell: cd: %s: No such file or directory\n", \
		line[1]), 1);
	getcwd(pwd, sizeof(pwd));
	change_pwd(env, pwd, oldpwd);
	g_status = 0;
	return (1);
}
