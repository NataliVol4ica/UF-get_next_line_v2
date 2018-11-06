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

/*static void		do_free(t_list **readlist, char **left, t_list *fd_elem)
{
	ft_lstdel(readlist, NULL);
	ft_memdel((void**)left);
	ft_memdel(&fd_elem->content);
}
*/
static t_list	*get_list_elem(const int fd)
{
	static t_list	*fd_list = NULL;
	t_list	*t;

	t = fd_list;
	while (t)
	{
		if (t->content_size == (size_t)fd)
			return (t);
		t = t->next;
	}
	if ((t = ft_lstnew(NULL, 0)))
	{
		t->content_size = (size_t)fd;
		ft_lstpushback(&fd_list, t);
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
		//printf("remainder check positive\n");
		rem[0] = 0;
		*line = ft_strdup(remainder);
		if (rem[1])
			fd_elem->content = (void*)ft_strdup(&rem[1]);
		else
			fd_elem->content = NULL;
		free(remainder);
		//ft_strleftshift(remainder, ft_strlen(remainder) + 1, ft_strlen(rem));
		return 1;
	}
	*pos = ft_strlen(remainder);
	if (*pos > 0)
		ft_strcpy(big_buf, remainder);
	free(remainder);
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

int				get_next_line(const int fd, char **line)
{
	static char *big_buf = NULL;
	//static int big_buf_size = BUFF_SIZE + 1000;
	static int big_buf_size = BUFF_SIZE + 1;
	int	ret;
	int	pos;
	t_list			*fd_elem;

	char *rem;

	if (!big_buf)
	{
		big_buf = (char*)malloc(sizeof(char) * big_buf_size);
		//printf("malloc ok\n");
	}
	
	fd_elem = get_list_elem(fd);
	//printf("remainder check ok\n");
	if (load_remainder(fd_elem, big_buf, &pos, line))
		return (1);
	//printf("remainder load ok\n");
	while ((ret = read(fd, &big_buf[pos], BUFF_SIZE)))
	{
		//printf("ret %d\n",ret);
		pos += ret;
		//printf("L: \"%s\"\n", big_buf);
		if (str_part_contains(big_buf, pos, ret))
			break;
		if (pos + BUFF_SIZE > big_buf_size - 1)
			realloc_buf(&big_buf, &big_buf_size);
	}
	//printf("met newline\n");
	if (pos == 0)
		return 0;
	big_buf[pos] = 0;
	rem = ft_strchr(big_buf, '\n');
	if (rem)
	{
		rem[0] = 0;
		if (rem[1])
			fd_elem->content = (void*)ft_strdup(&rem[1]);
		else
			fd_elem->content = NULL;
	}
	*line = ft_strdup(big_buf);
	return 1;
}
//	

	/*char			*left;
	char			*temp;
	char			*cont;
*/
//	if (BUFF_SIZE <= 0 || fd < 0 || line == NULL)
//		return (-1);
	//if (read(fd, buf, 0) < 0)
	//	return (-1);
//	