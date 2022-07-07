/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:13:09 by mmardi            #+#    #+#             */
/*   Updated: 2022/06/28 15:27:22 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strchr(char *str, char c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	size_t		i;
// 	size_t		j;
// 	int			k;
// 	char		*ptr;

// 	i = -1;
// 	k = 0;
// 	if (!s2)
// 	{
// 		s2 = malloc(sizeof(char) * 1);
// 		s2[0] = '\0';
// 	}
// 	if (!s1)
// 	{
// 		s1 = malloc(sizeof(char) * 1);
// 		s1[0] = '\0';
// 		k = 1;
// 	}
// 	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!ptr)
// 		return (NULL);
// 	while (s1[++i])
// 		ptr[i] = s1[i];
// 	j = 0;
// 	while (s2[j])
// 		ptr[i++] = s2[j++];
// 	ptr[i] = '\0';
// 	if (k)
// 		free(s1);
// 	return (ptr);
// }

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*hay;

	i = 0;
	hay = (char *)haystack;
	if (!needle[i] || hay == needle)
		return ((char *)hay);
	while (hay[i] && i < len)
	{
		j = 0;
		while (needle[j] && hay[i + j] == needle[j] && i + j < len)
		{
			if (needle[j + 1] == '\0')
				return (hay + i + j + 1);
			j++;
		}
		i++;
	}
	return (NULL);
}
