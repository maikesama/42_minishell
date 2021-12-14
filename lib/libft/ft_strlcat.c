/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 18:14:16 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/12 18:14:21 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	t_size	srclen;
	t_size	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstlen + 1 < dstsize)
	{
		ft_strlcpy(&dst[dstlen], src, (dstsize - dstlen));
		dst[dstsize - 1] = '\0';
	}
	if (dstsize < dstlen)
		return (dstsize + srclen);
	else
		return (dstlen + srclen);
}
