/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <nkolosov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:04:33 by nkolosov          #+#    #+#             */
/*   Updated: 2018/11/05 20:04:35 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 5

# include "libft.h"

typedef struct	s_data
{
	char	*big_buf;
	int		big_buf_size;
	t_list	*fd_list;
}				t_data;

typedef struct	s_vars
{
	int		ret;
	int		pos;
	t_list	*fd_elem;
	char	*rem;
}				t_vars;

int				get_next_line(const int fd, char **line);

#endif
