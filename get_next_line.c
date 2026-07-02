/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmassot <bmassot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:07:13 by bmassot           #+#    #+#             */
/*   Updated: 2025/10/13 16:22:19 by bmassot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	stash = trim_stash(stash);
	return (line);
}
/*
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file1.txt", O_RDONLY);
    if (fd < 0)
    {
        printf("Erreur ouverture fichier\n");
        return 1;
    }
    
    char *line;
    while ((line = get_next_line(fd)))
    {
        printf("Ligne lue: %s", line);
        free(line);
    }
    
    close(fd);
    return 0;
}
*/