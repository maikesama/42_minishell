/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:33:40 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/25 13:33:44 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size	ft_min_bonus(const t_size s1, const t_size s2)
{
	if (s1 < s2)
		return (s1);
	else
		return (s2);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (0);
	if (start >= (unsigned int)ft_strlen(s))
	{
		ptr = ft_calloc(1, sizeof(*ptr));
		return (ptr);
	}
	ptr = ft_calloc(ft_min_bonus(len, ft_strlen(s)) + 1, sizeof(*ptr));
	ft_strlcpy(ptr, &s[start], len + 1);
	return (ptr);
}
