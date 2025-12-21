/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeremy <mjeremy@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:41:41 by ikota             #+#    #+#             */
/*   Updated: 2025/10/01 15:57:04 by mjeremy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static char	*extract_line(char *buf)
{
	size_t	len;
	char	*line;

	len = 0;
	while (buf[len] && buf[len] != '\n')
		len++;
	if (buf[len] == '\n')
		line = malloc((len + 2) * sizeof(char));
	else
		line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_memcpy_gnl(line, buf, len);
	if (buf[len] == '\n')
	{
		line[len] = '\n';
		line[len + 1] = '\0';
	}
	else
		line[len] = '\0';
	return (line);
}

static char	*update_buf(char *buf)
{
	size_t	i;
	size_t	j;
	char	*new_buf;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i] || !buf[++i])
		return (free(buf), NULL);
	j = 0;
	while (buf[i + j])
		j++;
	if (j == 0)
		return (free(buf), NULL);
	new_buf = malloc((j + 1) * sizeof(char));
	if (!new_buf)
		return (NULL);
	j = 0;
	while (buf[i])
		new_buf[j++] = buf[i++];
	new_buf[j] = '\0';
	free(buf);
	return (new_buf);
}

static char	*read_and_append(int fd, char *buf)
{
	char	*tmp;
	ssize_t	buffer_read;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	buffer_read = 1;
	while (!ft_strchr_gnl(buf, '\n') && buffer_read > 0)
	{
		buffer_read = read(fd, tmp, BUFFER_SIZE);
		if (buffer_read < 0)
			return (free(tmp), free(buf), NULL);
		tmp[buffer_read] = '\0';
		buf = ft_strjoin_gnl(buf, tmp);
	}
	free(tmp);
	if (buffer_read == 0 && buf && *buf == '\0')
		return (free(buf), NULL);
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = read_and_append(fd, buf);
	if (!buf || *buf == '\0')
	{
		if (buf)
			free(buf);
		buf = NULL;
		return (NULL);
	}
	line = extract_line(buf);
	buf = update_buf(buf);
	return (line);
}

// int main(void)
// {
// 	#include <fcntl.h>
// 	#include <stdio.h>

// 	char	*line;
// 	int fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		return (-1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }

//read's buf Reads data from fd for the area specified by byte
//and stores it in buf.
//return value of read is how much data is read or -1 if it fails.
//read must write to an allocated array or malloc'd area every time,
//so temporarily allocate it with temp[].
//read() returns 0 (EOF)
//take a lot of data with BUFFER_SIZE and take out one line of them,
//although there are new-line characters in them. BUFFER_SIZE is used to
//take out a lot of line feed characters.
//The order of the conditions in the if statement is important,
//so check that the destination pointed to by buf itself is not NULL first.
// After freeing, buf still has the previous memory. The pointer in this state
//is called a dangling pointer.
