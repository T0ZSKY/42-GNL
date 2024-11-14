/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomlimon <tom.limon@>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 12:36:11 by tomlimon          #+#    #+#             */
/*   Updated: 2024/11/14 15:52:01 by tomlimon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		line = ft_substr(str, 0, i + 1);
	else
		line = ft_substr(str, 0, i);
	return (line);
}

char	*update_static_buffer(char *buffer, int start)
{
	int		len;
	char	*new_buffer;

	len = 0;
	while (buffer[start + len])
		len++;
	new_buffer = ft_substr(buffer, start, len);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		tmp[BUFFER_SIZE + 1];
	char		*line;
	int			byte_read;

	if (!buffer)
		buffer = ft_strdup("");
	while (!ft_strchr(buffer, '\n'))
	{
		byte_read = read(fd, tmp, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(buffer), buffer = NULL, NULL);
		tmp[byte_read] = '\0';
		buffer = ft_strjoin_custom(buffer, tmp);
		if (byte_read == 0)
			break ;
	}
	if (!*buffer)
		return (free(buffer), buffer = NULL, NULL);
	line = ft_line(buffer);
	buffer = update_static_buffer(buffer, ft_strlen(line));
	return (line);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	copy_strings(char *dest, const char *src, int start)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[start + i] = src[i];
		i++;
	}
}
