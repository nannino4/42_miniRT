/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:25:01 by gcefalo           #+#    #+#             */
/*   Updated: 2021/04/06 16:54:07 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

size_t	ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t			i;

	i = 0;
	while (src[i] != 0)
	{
		if (i + 1 < size)
			dst[i] = src[i];
		if (i + 1 == size)
			dst[i] = 0;
		i++;
	}
	if (i + 1 <= size)
		dst[i] = 0;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		dst_len;
	size_t		src_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size > 0 && dst_len < (size - 1))
	{
		i = 0;
		while (src[i] && (dst_len + i) < (size - 1))
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = 0;
	}
	if (dst_len > size)
		dst_len = size;
	return (dst_len + src_len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (0);
	if (ft_strlen(s) <= start || start < 0)
	{
		ft_strlcpy(str, s, 1);
		return (str);
	}
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*s;
	size_t		len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = malloc(len);
	ft_strlcpy(s, s1, len);
	ft_strlcat(s, s2, len);
	return (s);
}
