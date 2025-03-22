/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aitafern <aitafern@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:31:40 by aitafern          #+#    #+#             */
/*   Updated: 2025/03/21 19:03:12 by aitafern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 13
# endif

typedef struct s_buffer_struct
{
	char			*buf;
	char			*next_data;
	unsigned int	buffer_size;
	char			*nlpos;
	char			*line;
	char			*aux;
	ssize_t			bytes_read;
	size_t			len;
}	t_buf_st;

# ifndef FD_MAX
#  define FD_MAX 4096
# endif

char	*get_next_line(int fd);
ssize_t	read_for_buf(int fd, t_buf_st *buf_struct);
size_t	gnl_strlen(char *str);
char	*gnl_strjoin(char *str1, char *str2, size_t len);
char	*nl_strchr(char *str);
char	*nl_located(t_buf_st *bs);
char	*pre_valid(int fd, t_buf_st *bs);

#endif