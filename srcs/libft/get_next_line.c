/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcefalo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 17:24:41 by gcefalo           #+#    #+#             */
/*   Updated: 2021/02/27 10:57:13 by gcefalo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char		*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	if ((str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1))) == 0)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

int			find_ch(char const *s, char c)
{
	int		i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int			set_line_and_return(int n, char **line, int fd, char **s)
{
	char	*tmp;

	if (n == 0 && find_ch(s[fd], '\n') == -1)
	{
		if (!(*line = ft_substr(s[fd], 0, ft_strlen(s[fd]))))
			return (-1);
		free(s[fd]);
		s[fd] = 0;
		return (0);
	}
	else if (n >= 0 && find_ch(s[fd], '\n') != -1)
	{
		if (!(*line = ft_substr(s[fd], 0, find_ch(s[fd], '\n'))))
			return (-1);
		tmp = ft_substr(s[fd], find_ch(s[fd], '\n') + 1, ft_strlen(s[fd]));
		free(s[fd]);
		s[fd] = tmp;
		return (1);
	}
	return (-1);
}

int			set_s(char **s, int fd)
{
	if (!s[fd])
	{
		if (!(s[fd] = ft_strdup("")))
			return (-1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char		*s[256];
	char			*tmp;
	int				n;
	char			buf[BUFFER_SIZE + 1];

	if (BUFFER_SIZE <= 0 || !line || fd < 0 || read(fd, buf, 0) < 0)
		return (-1);
	*line = 0;
	n = 0;
	if (set_s(s, fd) == -1)
		return (-1);
	if (find_ch(s[fd], '\n') == -1)
	{
		while ((n = read(fd, buf, BUFFER_SIZE)) > 0)
		{
			buf[n] = 0;
			if (!(tmp = ft_strjoin(s[fd], buf)))
				return (-1);
			free(s[fd]);
			s[fd] = tmp;
			if (find_ch(s[fd], '\n') != -1)
				break ;
		}
	}
	return (set_line_and_return(n, line, fd, s));
}
