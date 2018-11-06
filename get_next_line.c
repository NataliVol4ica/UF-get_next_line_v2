/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <nkolosov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:04:17 by nkolosov          #+#    #+#             */
/*   Updated: 2018/11/05 20:04:19 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//todo: rm extra libraries

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"
#include "libft.h"
#include "get_next_line.h"

static t_list	*get_list_elem(t_data *data, const int fd)
{
	t_list	*t;

	t = data->fd_list;
	while (t)
	{
		if (t->content_size == (size_t)fd)
			return (t);
		t = t->next;
	}
	if ((t = ft_lstnew(NULL, 0)))
	{
		t->content_size = (size_t)fd;
		ft_lstpushback(&data->fd_list, t);
		return (t);
	}
	return (NULL);
}

int str_part_contains(char *str, int pos, int len)
{
	for (int i = 0; i < len; i++)
		if (str[pos - i - 1] == '\n')
			return 1;
	return 0;
}

int	load_remainder(t_list *fd_elem, char *big_buf, int *pos, char **line)
{
	char *remainder;
	char *rem;

	remainder = (char*)fd_elem->content;
	if ((rem = ft_strchr(remainder, '\n')))
	{
		rem[0] = 0;
		*line = ft_strdup(remainder);
		if (rem[1])
			fd_elem->content = (void*)ft_strdup(&rem[1]);
		else
			fd_elem->content = NULL;
		free(remainder);		
		return 1;
	}
	*pos = ft_strlen(remainder);
	if (*pos > 0)
	{
		ft_strcpy(big_buf, remainder);
		free(remainder);
		fd_elem->content = NULL;
	}
	return 0;
}

void realloc_buf(char **buf, int *big_buf_size)
{
	int new_size = *big_buf_size * 4;
	char *new_buf = (char*)malloc(sizeof(char) * new_size);
	char *to_del = *buf;
	ft_strncpy(new_buf, *buf, *big_buf_size);
	*big_buf_size = new_size;
	*buf = new_buf;
	free(to_del);
}

void init_data(t_data **data)
{
	*data = (t_data)malloc(sizeof(t_data));
	*data->big_buf = (char*)malloc(sizeof(char) * big_buf_size);
	*data->big_buf_size = BUFF_SIZE + 1000;
	*data->fd_list = NULL;
}

int				get_next_line(const int fd, char **line)
{
	static t_data	*data;
	int				ret;
	int				pos;
	t_list			*fd_elem;
	char			*rem;

	if (BUFF_SIZE <= 0 || fd < 0 || line == NULL || read(fd, big_buf, 0) < 0)
		return (-1);
	if (!data)
		init_data(&data);
	fd_elem = get_list_elem(data, fd);
	if (load_remainder(fd_elem, data->big_buf, &pos, line))
		return (1);
	while ((ret = read(fd, &data->big_buf[pos], BUFF_SIZE)))
	{
		pos += ret;
		if (str_part_contains(data->big_buf, pos, ret))
			break;
		if (pos + BUFF_SIZE > data->big_buf_size - 1)
			realloc_buf(&data->big_buf, &big_buf_size);
	}
	if (pos == 0)
		return 0;
	data->big_buf[pos] = 0;
	rem = ft_strchr(data->big_buf, '\n');
	if (rem)
	{
		rem[0] = 0;
		if (rem[1])
			fd_elem->content = (void*)ft_strdup(&rem[1]);
		else
			fd_elem->content = NULL;
	}
	*line = ft_strdup(data->big_buf);
	return 1;
}
