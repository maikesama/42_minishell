/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:31:53 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/14 19:31:55 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	t_byte	*ptr;
	t_byte	*ptr2;

	ptr = (t_byte *)src;
	ptr2 = (t_byte *)dst;
	if (!(dst) && !(src))
		return (0);
	while (n)
	{
		*ptr2 = *ptr;
		ptr2++;
		ptr++;
		n--;
	}
	return (dst);
}
