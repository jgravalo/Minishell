/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtome-pe <dtome-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:07:25 by dtome-pe          #+#    #+#             */
/*   Updated: 2023/05/29 13:41:19 by dtome-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*ft_get_free(char *tmp)
{
	free (tmp);
	tmp = NULL;
	return (NULL);
}

static char	*remove_string(char *tmp)
{
	size_t		len;
	char		*new_tmp;
	size_t		n;

	len = ft_get_strchr(tmp, '\n', ft_get_strlen(tmp));
	n = ft_get_strlen(tmp);
	if (len == n)
	{
		free (tmp);
		tmp = NULL;
		return (tmp);
	}
	else
	{
		new_tmp = (char *)malloc(sizeof (char) * (n - len + 1));
		if (!new_tmp)
			return (ft_get_free(tmp));
		ft_get_strlcpy(new_tmp, tmp, n - len + 1, len);
		free (tmp);
		tmp = NULL;
	}
	return (new_tmp);
}

static char	*create_string(char *tmp, char c, size_t n)
{
	size_t	len;
	char	*string;

	len = 0;
	len = ft_get_strchr(tmp, c, n);
	string = (char *)malloc(sizeof (char) * (len + 1));
	if (!string)
	{	
		free (string);
		string = NULL;
		return (NULL);
	}
	ft_get_strlcpy(string, tmp, len + 1, 0);
	return (string);
}

static char	*create_nullstring(char **tmp, char *line)
{
	size_t	len;

	if (!*tmp)
		return (NULL);
	len = 0;
	len = ft_get_strlen(*tmp);
	line = (char *)malloc(sizeof (char) * (len + 1));
	if (!line)
	{	
		free (line);
		line = NULL;
		free (*tmp);
		*tmp = NULL;
		return (NULL);
	}
	ft_get_strlcpy(line, *tmp, len + 1, 0);
	free (*tmp);
	*tmp = NULL;
	return (line);
}

char	*get_next_line(int fd)
{	
	int				bytes;
	char			buf[BUFFER_SIZE];
	static char		*tmp;
	char			*line;

	line = NULL;
	while (1)
	{	
		bytes = read(fd, buf, BUFFER_SIZE);
		if ((bytes == 0 && tmp == NULL) || bytes == -1)
			return (tmp = ft_get_free(tmp));
		tmp = ft_get_strjoin(tmp, buf, bytes);
		if (ft_get_strchr(tmp, '\n', ft_get_strlen(tmp)) != 0)
		{
			line = create_string(tmp, '\n', ft_get_strlen(tmp));
			if (!line)
				tmp = ft_get_free(tmp);
			tmp = remove_string(tmp);
			return (line);
		}
		else if (bytes == 0 && ft_get_strlen(tmp) > 0)
			return (line = create_nullstring(&tmp, line));
	}
}
