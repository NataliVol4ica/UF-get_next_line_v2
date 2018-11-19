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

#include <stdlib.h>
#include <unistd.h>
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

static int		load_remainder(t_list *fd_elem,
						char *big_buf, int *pos, char **line)
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
		return (1);
	}
	*pos = ft_strlen(remainder);
	if (*pos > 0)
	{
		ft_strcpy(big_buf, remainder);
		free(remainder);
		fd_elem->content = NULL;
	}
	return (0);
}

static void		realloc_buf(t_data *data)
{
	int		new_size;
	char	*new_buf;
	char	*to_del;

	new_size = data->big_buf_size * 4;
	new_buf = (char*)malloc(sizeof(char) * new_size);
	to_del = data->big_buf;
	ft_strncpy(new_buf, data->big_buf, data->big_buf_size);
	data->big_buf_size = new_size;
	data->big_buf = new_buf;
	free(to_del);
}

static int		get_next_line_part_2(t_data *data, t_vars *vars,
										char **line)
{
	if (vars->pos == 0)
		return (0);
	data->big_buf[vars->pos] = 0;
	vars->rem = ft_strchr(data->big_buf, '\n');
	if (vars->rem)
	{
		vars->rem[0] = 0;
		if (vars->rem[1])
			vars->fd_elem->content = (void*)ft_strdup(&vars->rem[1]);
		else
			vars->fd_elem->content = NULL;
	}
	*line = ft_strdup(data->big_buf);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_data	*data;
	t_vars			vars;

	if (!data)
	{
		data = (t_data*)malloc(sizeof(t_data));
		data->big_buf_size = BUFF_SIZE + 1000;
		data->big_buf = (char*)malloc(sizeof(char) * data->big_buf_size);
		data->fd_list = NULL;
	}
	if (BUFF_SIZE <= 0 || fd < 0 || line == NULL ||
		read(fd, data->big_buf, 0) < 0)
		return (-1);
	vars.fd_elem = get_list_elem(data, fd);
	if (load_remainder(vars.fd_elem, data->big_buf, &vars.pos, line))
		return (1);
	while ((vars.ret = read(fd, &data->big_buf[vars.pos], BUFF_SIZE)))
	{
		vars.pos += vars.ret;
		if (ft_strnchr(data->big_buf, vars.pos, vars.ret))
			break ;
		if (vars.pos + BUFF_SIZE > data->big_buf_size - 1)
			realloc_buf(data);
	}
	return (get_next_line_part_2(data, &vars, line));
}
