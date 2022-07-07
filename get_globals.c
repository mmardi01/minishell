/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_globals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:43:57 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/22 15:53:52 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_globale(int i)
{	
	static int	j;

	if (i == 0)
		j = 0;
	else if (i == 1)
		j = 1;
	else
		return (j);
	return (j);
}

int	get_glo_2(int n)
{
	static int	i;

	if (n == 1)
		i = 1;
	else if (n == 0)
		i = 0;
	else
		return (i);
	return (i);
}
