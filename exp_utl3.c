/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utl3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:03:57 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/27 14:45:33 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_alphanum(char s)
{
	if ((s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z')
		|| (s <= '9' && s >= '0') || s == '_')
		return (1);
	else
		return (0);
}

int	ft_is_alpha(char s)
{
	if ((s >= 'A' && s <= 'Z') || (s >= 'a' && s <= 'z') || s == '_')
		return (1);
	else
		return (0);
}

int	check_arg(char *cmd)
{
	int	i;
	int	a;
	int	p;

	p = 0;
	a = 0;
	i = 0;
	if (!ft_is_alpha(cmd[0]))
	{
		printf("minishell: export: %s: invalid option\n", cmd);
		return (1);
	}
	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!ft_is_alphanum(cmd[i]))
		{
			if (cmd[i] == '+' && cmd[i + 1] == '=')
				break ;
			printf("minishell: export: %s: invalid option\n", cmd);
			return (1);
		}
		i++;
	}
	return (0);
}
