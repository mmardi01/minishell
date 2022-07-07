/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 20:23:37 by mmardi            #+#    #+#             */
/*   Updated: 2022/07/07 12:52:02 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_n(char **str, int *i)
{
	int	j;
	int	k;

	j = 0;
	while (str[j])
	{
		k = 1;
		if (str[j][0] == '-' && str[j][k] == 'n')
		{
			while (str[j][k])
			{
				if (str[j][k] != 'n')
				{
					*i += j;
					return ;
				}
				k++;
			}
		}
		else
			break ;
		j++;
	}
	*i += j;
}

int	ft_echo(char **str, int fd)
{
	int		i;
	int		j;

	i = 1;
	g_status = 0;
	if (str[1] == NULL)
	{
		ft_putstr_fd("\n", fd);
		return (1);
	}
	ft_check_n(&str[1], &i);
	j = i;
	while (str[i])
	{
		ft_putstr_fd(str[i], fd);
		i++;
		if (str[i] != NULL)
			ft_putstr_fd(" ", fd);
	}
	if (j == 1)
		ft_putstr_fd("\n", fd);
	return (1);
}

int	ft_check_command(char **str, char **env, int fd)
{
	int	i;

	i = 1;
	if (!str[0])
		return (0);
	if (ft_strcmp(str[0], "echo") == 0)
		return (ft_echo(str, fd));
	if (ft_strcmp(str[0], "cd") == 0)
		return (ft_cd(str, env));
	if (ft_strcmp(str[0], "pwd") == 0)
		return (ft_pwd(fd));
	if (ft_strcmp(str[0], "export") == 0)
		return (ft_export(str, env, fd));
	if (ft_strcmp(str[0], "unset") == 0)
		return (ft_unset(str, env));
	if (ft_strcmp(str[0], "env") == 0 && str[1] == '\0')
		return (ft_print_env(env, fd));
	if (ft_strcmp(str[0], "exit") == 0)
		return (ft_exit(str), 1);
	g_status = 127;
	return (0);
}

void	ft_ctrlc(int sig)
{
	if (sig == SIGINT && !get_globale(2))
	{
		g_status = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
}
