/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:40:57 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/18 15:40:59 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const t_byte	*s;
	t_byte			*d;
	t_byte			*revd;
	const t_byte	*revs;

	s = src;
	revs = s + (len - 1);
	d = dst;
	revd = d + (len - 1);
	if (s < d)
	{
		while (len--)
		{
			*revd-- = *revs--;
		}
		return (dst);
	}
	return (ft_memcpy(d, s, len));
}
