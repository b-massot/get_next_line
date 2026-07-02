/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapetros <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 22:35:42 by dapetros          #+#    #+#             */
/*   Updated: 2025/10/13 09:30:06 by bmassot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	if ((unsigned char)c == 0)
		return (&str[i]);
	return (NULL);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(s1);
	return (new);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && (i < size - 1))
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	unsigned char	*srcs;
	unsigned char	*dest;
	size_t			dlen;
	size_t			space;

	if (!src && !dst)
		return (0);
	if (dsize == 0)
		return (ft_strlen(src));
	dlen = (size_t)ft_strlen(dst);
	if (dlen >= dsize)
		return (dsize + ft_strlen(src));
	srcs = (unsigned char *)src;
	dest = (unsigned char *)dst;
	while (*dest)
		dest++;
	space = dsize - dlen - 1;
	while (space-- > 0 && *srcs)
	{
		*dest = *srcs;
		dest++;
		srcs++;
	}
	*dest = '\0';
	return (ft_strlen(src) + dlen);
}
