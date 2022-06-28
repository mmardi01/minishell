/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:56:42 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/26 16:48:13 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		a;
	long	c;

	i = 0;
	a = 1;
	c = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			a = -a;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		c = c * 10 + (str[i] - '0');
		i++;
	}
	return (a * c);
}

int	strdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

void	ft_exit(char **str)
{	
	if (!str[1])
	{
		write(1, "exit\n", 5);
		exit (0);
	}
	else if (strdigit(str[1]) && !str[2] && \
	(ft_atoi(str[1]) >= -2147483648 && ft_atoi(str[1]) <= 2147483647))
	{
		write(1, "exit\n", 5);
		exit (ft_atoi(str[1]));
	}
	else if (!str[2])
	{
		write(1, "exit\n", 5);
		printf("minishell: exit: %s: numeric argument required\n", str[1]);
		exit (0);
	}
	printf("minishell: exit: too many arguments\n");
}
