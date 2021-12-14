/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:20:51 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/26 17:20:54 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_digits_counter(long int n)
{
	int		needed;

	needed = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		needed++;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		needed++;
	}
	return (needed);
}

char	*ft_convert(char *str, long int n, int len)
{
	if (n < 0)
	{
		*str = '-';
		n *= -1;
	}
	if (n == 0)
	{
		*str = '0';
		return (str);
	}
	while (n > 0)
	{
		str[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = ft_digits_counter((long int)n);
	str = ft_calloc(len + 1, sizeof(*str));
	return (ft_convert(str, (long int)n, len));
}
