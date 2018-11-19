/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <nkolosov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 16:21:34 by nkolosov          #+#    #+#             */
/*   Updated: 2017/10/25 16:21:34 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strnchr(char *str, int pos, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if (str[pos - i - 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}
