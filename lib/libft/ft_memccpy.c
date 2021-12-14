/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 15:00:13 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/15 15:00:27 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	const t_byte	*ptr;
	t_byte			*ptr2;
	t_byte			chr;

	chr = c;
	ptr = src;
	ptr2 = dst;
	while (n)
	{
		if (*ptr == chr)
		{
			*ptr2++ = *ptr++;
			return (ptr2);
		}
		*ptr2 = *ptr;
		ptr2++;
		ptr++;
		n--;
	}
	return (0);
}
