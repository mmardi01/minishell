/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:47:04 by obraiki           #+#    #+#             */
/*   Updated: 2022/07/07 12:52:07 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i] && i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (i != n)
		return (str1[i] - str2[i]);
	return (0);
}

int	ft_is_str(char *line, char *str)
{
	int		i;

	if (!line || !str)
		return (0);
	if (ft_strlen(line) != ft_strlen(str))
		return (0);
	i = 0;
	while (str[i] && line[i] == str[i])
		i++;
	if (!str[i] && !line[i])
		return (1);
	return (0);
}

int	ft_pwd(int fd)
{
	char	cwd[10000];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("%s\n", "error");
	else
	{
		ft_putstr_fd(cwd, fd);
		ft_putstr_fd("\n", fd);
	}
	g_status = 0;
	return (1);
}
