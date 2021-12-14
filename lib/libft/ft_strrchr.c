/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:33:38 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/12 15:33:40 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	flag;
	int		len;

	flag = c;
	len = ft_strlen(str);
	str = &str[len];
	while (len >= 0)
	{
		if (*str == flag)
			return ((char *)str);
		str--;
		len--;
	}
	return (0);
}
