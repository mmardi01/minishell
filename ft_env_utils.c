/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 16:56:10 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/26 17:05:35 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_itoa(int j)
{
	char	*a;
	int		k;
	int		i;
	long	n;

	n = j;
	k = n_al(n);
	i = 0;
	a = malloc(k + 1);
	if (a == 0)
		return (0);
	if (n < 0)
	{
		a[0] = '-';
		n *= -1;
		i = 1;
	}
	a[k--] = '\0';
	print_n(a, i, k, n);
	return (a);
}

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i && s[i] != (char)c)
		i--;
	if (s[i] == (char)c)
		return (&((char *)s)[i]);
	return (NULL);
}

int	n_al(long n)
{
	long	i;
	long	k;

	i = 0;
	k = 0;
	if (n < 0)
	{
		k = 1;
		n *= -1;
	}
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i + 1 + k);
}

void	print_n(char *a, int ich, int k, long n)
{
	int	i;

	i = k;
	while (k-- >= ich)
	{
		a[i--] = '0' + (n % 10);
		n = n / 10;
	}
}
