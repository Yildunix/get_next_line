/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: endyildi <endyildi@mulhouse42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 22:03:23 by endyildi          #+#    #+#             */
/*   Updated: 2026/11/27 01:11:10 by endyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_join(int fd, char *stash)
{
    char *buff;
    int n;

    buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buff)
        return (NULL);
    while (!ft_strchr(stash, '\n'))
    {
        n = read(fd, buff, BUFFER_SIZE);
        if (n < 0)
        {
            free(buff);
            free(stash);
            return (NULL);
        }
        if (n == 0)
            break;
        buff[n] = '\0';
        stash = ft_strjoin(stash, buff);
        if (!stash)
	        break ;
    }
    free(buff);
    return (stash);
}

static char	*cut_line(char **stash)
{
    char *start;
	char *line;
	size_t  len;
	char *m;

	// if (!*stash || !**stash)
	// {
	// 	free(*stash);
	// 	*stash = NULL;
	// 	return (NULL);
	// }
	start = ft_strchr(*stash, '\n');
	if (start)
		len = start - *stash + 1 ;
	else
		len = ft_strlen(*stash);
	line = ft_substr(*stash, 0, len);
	m = NULL;
	if (line && (*stash)[len] != '\0')
	{
		m = ft_substr(*stash, len, ft_strlen(*stash) - len);
		if (!m)
		{
			free(line);
			line = NULL;
		}
	}
	free(*stash);
	*stash = m;
	return (line);
}

char *get_next_line(int fd)
{
	static char *stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_join(fd, stash);
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (cut_line(&stash));
}