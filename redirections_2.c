/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:55:11 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/28 21:18:30 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_output(char **spath, char **commands, char **env, t_fd *fd)
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
	if (pid == 0)
	{
		if (fd->pfd[0] != -1)
			dup2(fd->pfd[0], 0);
		if (fd->pfd2[1] != -1)
			dup2(fd->pfd2[1], 1);
		if (fd->pfd[1] != -1)
			dup2(fd->pfd[1], 1);
		if (fd->fd[0] != 0)
			dup2(fd->fd[0], 1);
		if (fd->fd[1] != 0)
			dup2(fd->fd[1], 0);
		execve(spath[i], commands, env);
	}
	return (g_status = 0, 1);
}

void	redirect_in_out(char **spath, char **ocommands, char **env, t_fd *fd)
{
	int	j;

	j = 0;
	if (!ocommands[0])
		return ;
	if (fd->pfd[1] != -1)
		j = ft_check_command(ocommands, env, fd->pfd[1]);
	if (fd->pfd2[1] != -1)
		j = ft_check_command(ocommands, env, fd->pfd[1]);
	if (fd->fd[0] != 0 || fd->fd[1] != 0)
		j = ft_check_command(ocommands, env, fd->fd[0]);
	if (j == 0)
		if (exec_output(spath, ocommands, env, fd) == 0)
			printf("minishell: %s: command not found\n", ocommands[0]);
	ft_free(ocommands);
}

int	*get_fd(char **commands, t_fd *fd)
{
	int		i;

	i = -1;
	fd->fd[0] = 0;
	fd->fd[1] = 0;
	while (commands[++i])
	{
		if (commands[i][0] == '>' && commands[i][1] == '\0')
		{
			open(commands[i + 1], O_CREAT | O_TRUNC | O_RDWR, 0777);
			if (check_next_red(&commands[i + 1], '>'))
				fd->fd[0] = open(commands[i + 1], O_TRUNC | O_RDWR, 0777);
		}
		else if (commands[i][0] == '>' && commands[i][1] == '>')
		{
			open(commands[i + 1], O_CREAT | O_RDONLY | O_APPEND, 0777);
			if (check_next_red(&commands[i + 1], '>'))
				fd->fd[0] = open(commands[i + 1], O_WRONLY | O_APPEND);
		}
		else if (commands[i][0] == '<')
			fd->fd[1] = get_fd2(&commands[i]);
	}
	return (0);
}

void	redirect2(char **commands, char **env, t_fd *fd)
{
	char	**ocommands;
	char	*path;
	char	**spath;
	int		i;

	path = get_env("PATH=", env);
	spath = ft_split(path, ':');
	ocommands = only_commands(commands);
	add_to_path(spath, ocommands[0]);
	get_fd(commands, fd);
	redirect_in_out(spath, ocommands, env, fd);
	get_globale(1);
	waitpid(-1, &i, 0);
	if (i == 256)
		g_status = 1;
	if (i == 2)
		g_status = 130;
	unlink("../.a");
	ft_free(spath);
	if (fd->fd[0] > 2)
		close(fd->fd[0]);
	if (fd->fd[1] > 2)
		close(fd->fd[1]);
}

void	redirect(char **commands, char **env)
{
	t_fd	fd;

	fd.pfd[0] = -1;
	fd.pfd[1] = -1;
	fd.pfd2[1] = -1;
	if (check_next_red(commands, '|') == 0)
		mypipe(commands, env, &fd);
	else
		redirect2(commands, env, &fd);
}
