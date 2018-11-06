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

static t_list	*get_list_elem(t_list **l, const int fd)
{
	t_list	*t;

	t = *l;
	while (t)
	{
		if (t->content_size == (size_t)fd)
			return (t);
		t = t->next;
	}
	if ((t = ft_lstnew(NULL, 0)))
	{
		t->content_size = (size_t)fd;
		ft_lstpushback(l, t);
		return (t);
	}
	return (NULL);
}
*/

int str_part_contains(char *str)
{
	for (int i= 0; i < BUFF_SIZE; i++)
		if (str[i] == '\n')
			return 1;
	return 0;
}

int				get_next_line(const int fd, char **line)
{
	static char *left_ptr = NULL;
	static char *big_buf;

	int	ret;
	int	pos;
	int big_buf_size;

	big_buf_size = 1000 + BUFF_SIZE - 1000 % BUFF_SIZE;
	if (!left_ptr)
	{
		big_buf = (char*)malloc(sizeof(char) * big_buf_size);
		left_ptr = big_buf;
	}
	pos = left_ptr - big_buf;
	//else
	//	big_buf = left_ptr;
	while ((ret = read(fd, &big_buf[pos], BUFF_SIZE)))
	{
		//printf("ret %d\n",ret);
		if (str_part_contains(&big_buf[pos]))
			break;
		pos += BUFF_SIZE;
		big_buf[pos] = 0;
		printf("The line is \"%s\"\n", big_buf);
		if (pos + BUFF_SIZE > big_buf_size)
		{
			printf("overflow big buf\n");
			exit(0);
			break;//todo:realloc
		}

	}
	//printf("ret %d\n",ret);
	if (ret == 0)
		return 0;
	*line = left_ptr;
	left_ptr = ft_strchr(left_ptr, '\n');
	if (!left_ptr)//esli eto last
	{
		//printf("left ptr is null %d\n",ret);
		return 0;
	}
	left_ptr[0] = '\0';
	left_ptr++;
	return 1;
}
//	static t_list	*fd_list = NULL;
//	t_list			*fd_elem;

	/*char			*left;
	char			*temp;
	char			*cont;
*/
//	if (BUFF_SIZE <= 0 || fd < 0 || line == NULL)
//		return (-1);
	//if (read(fd, buf, 0) < 0)
	//	return (-1);
//	fd_elem = get_list_elem(&fd_list, fd);