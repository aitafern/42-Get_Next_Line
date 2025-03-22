/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitafern <aitafern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 10:59:46 by aitafern          #+#    #+#             */
/*   Updated: 2025/03/21 17:46:05 by aitafern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *str)
{
	size_t	len;

	if (str == NULL)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

//len = number of characters of str2 to copy untill /n included
char	*gnl_strjoin(char *str1, char *str2, size_t len)
{
	char	*new_str;
	char	*pnew_str;
	size_t	size;

	size = gnl_strlen(str1) + (len + 1);
	new_str = NULL ;
	if (size > 0)
		new_str = malloc(size * sizeof (char));
	if (new_str == NULL)
		return (str1);
	pnew_str = new_str;
	if (str1 != NULL)
	{
		while (*str1)
			*pnew_str++ = *str1++;
	}
	while (len > 0)
	{
		*pnew_str++ = *str2++;
		len--;
	}
	new_str[size - 1] = '\0';
	return (new_str);
}

char	*nl_strchr(char *str)
{
	if (str != NULL)
	{
		while (*str != '\0' && *str != '\n')
			str++;
		if (*str == '\0')
			str = NULL;
	}
	return (str);
}

char	*nl_located(t_buf_st *bs)
{
	size_t	len;
	char	*update_line;

	len = (bs->nlpos - bs->next_data) + 1;
	update_line = gnl_strjoin(bs->line, bs->next_data, len);
	if (update_line == NULL)
		return (bs->line);
	bs->next_data = bs->nlpos + 1;
	free(bs->line);
	return (update_line);
}

char	*pre_valid(int fd, t_buf_st *bs)
{
	if (fd < 0 || bs == NULL || bs->buf == NULL || bs->buffer_size == 0)
		return (NULL);
	bs->line = NULL;
	return (bs->line);
}
