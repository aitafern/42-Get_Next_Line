/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitafern <aitafern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:50:32 by aitafern          #+#    #+#             */
/*   Updated: 2025/03/21 18:00:12 by aitafern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*free_mem(t_buf_st *buf_struct)
{
	if (buf_struct == NULL)
		return (NULL);
	if (buf_struct->buf != NULL)
		free(buf_struct->buf);
	free(buf_struct);
	return (NULL);
}

t_buf_st	*init_bs(unsigned int buffer_size)
{
	t_buf_st	*buf_struct;

	if (buffer_size == 0)
		return (NULL);
	buf_struct = malloc(sizeof(t_buf_st));
	if (buf_struct == NULL)
		return (NULL);
	buf_struct->buf = malloc((buffer_size + 1) * sizeof(char));
	if (buf_struct->buf == NULL)
		return (free_mem(buf_struct));
	buf_struct->buf[0] = '\0';
	buf_struct->next_data = NULL;
	buf_struct->buffer_size = buffer_size;
	buf_struct->nlpos = NULL;
	buf_struct->line = NULL;
	buf_struct->aux = NULL;
	buf_struct->bytes_read = 0;
	return (buf_struct);
}

ssize_t	read_for_buf(int fd, t_buf_st *buf_struct)
{
	ssize_t	bytes_read;

	if (fd < 0 || buf_struct == NULL || buf_struct->buf == NULL )
		return (0);
	bytes_read = read(fd, buf_struct->buf, buf_struct->buffer_size);
	if (bytes_read < 0)
	{
		buf_struct->buf[0] = '\0';
		buf_struct->next_data = NULL;
		return (-1);
	}
	else if (bytes_read == 0)
	{
		buf_struct->buf[0] = '\0';
		buf_struct->next_data = NULL;
		return (0);
	}
	buf_struct->buf[bytes_read] = '\0';
	buf_struct->next_data = buf_struct->buf;
	return (bytes_read);
}

char	*extract_line(int fd, t_buf_st *bs)
{
	pre_valid(fd, bs);
	while (1)
	{
		if (bs->next_data == NULL || *bs->next_data == '\0')
		{
			bs->bytes_read = read_for_buf(fd, bs);
			if (bs->bytes_read < 0)
			{
				free(bs->line);
				return (NULL);
			}
			else if (bs->bytes_read == 0)
				return (bs->line);
		}
		bs->nlpos = nl_strchr(bs->next_data);
		if (bs->nlpos != NULL)
			return (nl_located(bs));
		bs->len = gnl_strlen(bs->next_data);
		bs->aux = gnl_strjoin(bs->line, bs->next_data, bs->len);
		if (bs->aux == NULL)
			return (bs->line);
		free(bs->line);
		bs->line = bs->aux;
		bs->next_data = NULL;
	}
}

char	*get_next_line(int fd)
{
	static t_buf_st	*bs;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	if (bs == NULL)
		bs = init_bs(BUFFER_SIZE);
	if (bs == NULL)
		return (NULL);
	line = extract_line(fd, bs);
	if (line == NULL || (bs != NULL && bs->next_data == NULL
			&& (bs->buf == NULL || bs->buf[0] == '\0')))
	{
		bs = free_mem(bs);
	}
	return (line);
}
