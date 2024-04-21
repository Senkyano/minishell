/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_yann.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rihoy <rihoy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:28:51 by yrio              #+#    #+#             */
/*   Updated: 2024/04/21 13:17:22 by rihoy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlcpy_gnl(char *dst, char *src, size_t size)
{
	size_t	tmp;
	size_t	size_src;

	if (!dst || !src)
		return (NULL);
	size_src = ft_strlen(src);
	if (size > 0)
	{
		tmp = 0;
		while (tmp < size_src && tmp < size - 1)
		{
			dst[tmp] = src[tmp];
			tmp++;
		}
		dst[tmp] = '\0';
	}
	return (dst);
}

char	*ft_strdup_gnl(char *str)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(str) + 1;
	dup = malloc(size * sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy_gnl(dup, str, size);
	return (dup);
}

char	*ft_strjoin_gnl(char *s1, char *s2, size_t size)
{
	char	*str;
	size_t	size_s1;

	if (!s1)
		return (NULL);
	if (!s2 || !s2[0])
		return (free(s1), NULL);
	size_s1 = ft_strlen(s1);
	str = malloc((size_s1 + size + 1) * sizeof(char));
	if (!str)
		return (free(s1), NULL);
	ft_strlcpy_gnl(str, s1, size_s1 + 1);
	ft_strlcpy_gnl((str + size_s1), s2, size + 1);
	free(s1);
	return (str);
}

int	putbuf(char *line, char *buf)
{
	char	*newline;
	int		to_copy;

	newline = ft_strchr(line, '\n');
	if (newline != NULL)
	{
		to_copy = newline - line + 1;
		ft_strlcpy_gnl(buf, newline + 1, BUFFER_SIZE + 1);
	}
	else
	{
		to_copy = ft_strlen(line);
		ft_strlcpy_gnl(buf, "", BUFFER_SIZE + 1);
	}
	return (to_copy);
}
/*
char	*get_next_line_yann(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			countread;
	int			to_copy;

	line = ft_strdup_gnl(buf);
	while (!ft_strchr(line, '\n') && (countread = \
	read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[countread] = '\0';
		line = ft_strjoin_gnl(line, buf, countread);
	}
	if (!ft_strlen(line))
		return (free(line), NULL);
	to_copy = putbuf(line, buf);
	line[to_copy] = '\0';
	return (line);
}


int	main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Does not open file");
		return (0);
	}
	line = get_next_line(0);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(0);
		if (line[0] == 'z')
			return (free(line), 1);
	}
	return (1);
}
*/
