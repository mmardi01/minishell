/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 14:24:58 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/27 21:54:23 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handledollar(char **s, int *tab)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i][0] == '$' && s[i][1] == '?' && s[i][2] == '\0')
// 			s[i] = ft_itoa(g_status);
// 		else if (s[i][0] == '$' && getenv(&s[i][1]) && !tab[i])
// 			s[i] = ft_strdup(getenv(&s[i][1]));
// 		else if (s[i][0] == '$' && !getenv(&s[i][1]) && s[i + 1] && !tab[i])
// 			s[i] = ft_strdup(s[i + 1]);
// 		else if (s[i][0] == '$' && !getenv(&s[i][1]) && !s[i + 1] && !tab[i])
// 			s[i] = NULL;
// 		i++;
// 	}
// 	s[i] = NULL;
// }

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
