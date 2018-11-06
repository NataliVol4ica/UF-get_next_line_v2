/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strleftshift.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <nkolosov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:34:42 by nkolosov          #+#    #+#             */
/*   Updated: 2018/11/06 15:34:54 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strleftshift(char *str, size_t len)
{
	size_t i;
	size_t stlen;

	stlen = ft_strlen(str);
	i = 0;
	while (i < stlen - len)
	{
		str[i] = str[i + len];
		i++;
	}
	str[i] = 0;
}
