/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:24:58 by mmardi            #+#    #+#             */
/*   Updated: 2022/07/07 12:50:51 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_next_red(char **str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i][0] == c)
			return (0);
		i++;
	}
	return (1);
}

void	middlepipe(char **commands, char **env, t_fd *fd)
{
	int		j[2];
	char	**cmd;

	if (check_next_red(commands, '|') == 0)
	{
		pipe(j);
		fd->pfd2[1] = j[1];
	}
	fd->pfd[0] = fd->k;
	cmd = cmd_btw_pipes(commands);
	redirect2(cmd, env, fd);
	close(fd->k);
	fd->k = j[0];
	fd->pfd[0] = -1;
	close(j[1]);
	if (check_next_red(commands, '|') != 0)
			fd->pfd2[1] = -1;
	ft_free(cmd);
}

void	mypipe(char **commands, char **env, t_fd *fd)
{
	int		k[2];
	char	**cmd;
	int		i;

	i = -1;
	pipe(k);
	while (commands[++i])
	{
		if (i == 0)
		{
			fd->pfd[1] = k[1];
			cmd = cmd_btw_pipes(&commands[i]);
			redirect2(cmd, env, fd);
			fd->pfd[1] = -1;
			close(k[1]);
			fd->k = k[0];
		}
		else if (commands[i][0] == '|')
			middlepipe(&commands[i + 1], env, fd);
	}
	ft_free(cmd);
}
