/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:18:51 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 13:39:11 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * It returns a string containing the first line of the string passed to it, or
 * NULL if there is no line
 * 
 * @param stash the string that contains the line we want to get
 * 
 * @return A string of characters that is the line of the file.
 */
char	*ft_get_line(char *stash)
{
	int		i;
	char	*str;

	i = 0;
	if (!stash[i])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		str[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		str[i] = stash[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/**
 * It takes a string, finds the first newline character, and returns a new 
 * string containing everything after the newline
 * 
 * @param stash the string that contains the leftover characters from the 
 * previous read
 * 
 * @return A pointer to a string.
 */
char	*ft_stash(char *stash)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlengnl(stash) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (stash[i])
		str[j++] = stash[i++];
	str[j] = '\0';
	free (stash);
	return (str);
}

/**
 * It reads from a file descriptor and stores the readed data in a string
 * 
 * @param fd file descriptor
 * @param stash the string that contains the leftover characters from the 
 * previous read.
 * 
 * @return A pointer to a string.
 */
char	*ft_read_and_stash(int fd, char *stash)
{
	char	*buf;
	int		readed;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	readed = 1;
	while (!ft_strchrgnl(stash, '\n') && readed != 0)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed < 0)
		{
			free(buf);
			return (NULL);
		}
		buf[readed] = '\0';
		stash = ft_strjoingnl(stash, buf);
	}
	free(buf);
	return (stash);
}

/**
 * Read from the file descriptor fd until a newline is found, and return the line
 * read
 * 
 * @param fd file descriptor
 * 
 * @return A line of text from the file descriptor.
 */
char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[OPEN_MAX];

	if (fd < 0)
		return (NULL);
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	if (fd >= 0)
	{
		stash[fd] = ft_read_and_stash(fd, stash[fd]);
		if (!stash[fd])
			return (NULL);
		line = ft_get_line(stash[fd]);
		stash[fd] = ft_stash(stash[fd]);
		return (line);
	}
	return (0);
}
