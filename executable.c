/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 19:29:02 by mmardi            #+#    #+#             */
/*   Updated: 2022/07/07 12:51:58 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigquit(void)
{
	write(1, "Quit: 3\n", 8);
	g_status = 131;
}

int	exec(char **spath, char **commands, char **env)
{
	int	i;
	int	pid;

	i = -1;
	while (spath[++i])
		if (access(spath[i], X_OK) == 0)
			break ;
	if (!spath[i])
		return (0);
	pid = fork();
	g_status = 0;
	if (pid == 0)
	{
		signal (SIGQUIT, NULL);
		execve(spath[i], commands, env);
	}
	get_globale(1);
	waitpid(pid, &i, 0);
	if (i == 256)
		g_status = 1;
	if (i == 2)
		g_status = 130;
	if (i == 3)
		ft_sigquit();
	return (1);
}

char	**add_to_path(char **spath, char *command)
{
	int	i;

	i = 0;
	if (!command)
		return (NULL);
	while (spath[i])
	{
		spath[i] = ft_strjoin(spath[i], "/");
		spath[i] = ft_strjoin(spath[i], command);
		i++;
	}
	return (spath);
}

int	executable(char **commands, char **env)
{
	char	*path;
	char	**spath;
	int		k;

	k = 1;
	if (!commands[0])
		return (1);
	path = get_env("PATH=", env);
	if (!path)
		return (0);
	if (get_glo_2(4) == 1)
	{
		g_status = 1;
		if (check_permession(commands))
			redirect(commands, env);
	}
	spath = ft_split(path, ':');
	add_to_path(spath, commands[0]);
	if (get_glo_2(4) != 1)
		k = exec(spath, commands, env);
	ft_free(spath);
	if (k == 0 && get_glo_2(4) != 1)
		k = exec(commands, commands, env);
	get_glo_2(0);
	return (k);
}
