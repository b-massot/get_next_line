/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <bmassot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 14:07:13 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/15 16:26:36 by bmassot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_to_stash(int fd, char *stash)
{
	char		*buffer;
	char		*joined;
	ssize_t		bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes] = 0;
		joined = ft_strjoin(stash, buffer);
		if (!joined)
		{
			free(stash);
			return (free(buffer), NULL);
		}
		stash = joined;
	}
	free(buffer);
	return (stash);
}

char	*extract_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;
	size_t	len;

	if (!stash || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	len = i + (stash[i] == '\n');
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < len)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = 0;
	return (line);
}

char	*trim_stash(char *stash)
{
	size_t	i;
	size_t	new_len;
	char	*new_stash;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	new_len = ft_strlen(stash + i + 1);
	new_stash = malloc(new_len + 1);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	ft_strlcpy(new_stash, stash + i + 1, new_len + 1);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = read_to_stash(fd, stash[fd]);
	if (!stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = extract_line(stash[fd]);
	stash[fd] = trim_stash(stash[fd]);
	return (line);
}
/*
int	main(void)
{
	int	fd1 = open("file1.txt", O_RDONLY);
	int	fd2 = open("file2.txt", O_RDONLY);
	char *line1;
	char *line2;

	while ((line1 = get_next_line(fd1)) || (line2 = get_next_line(fd2)))
	{
		if (line1)
		{
			write(1, line1, ft_strlen(line1));
			free(line1);
		}
		if (line2)
		{
			write(1, line2, ft_strlen(line2));
			free(line2);
		}
	}
	close(fd1);
	close(fd2);
	return (0);
}
*/
