/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_02.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:57:00 by mpaci             #+#    #+#             */
/*   Updated: 2021/11/08 14:57:02 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_nbrlen(long int n)
{
	static int	cnt;
	static int	flag;

	if (!flag)
	{
		flag++;
		cnt = 0;
	}
	if (n < 0)
		n *= -1;
	if (n >= 10)
		ft_pf_nbrlen(n / 10);
	flag = 0;
	return (++cnt);
}

int	ft_pf_nbrlen_hex(unsigned long int n)
{
	static int	cnt;
	static int	flag;

	if (!flag)
	{
		flag++;
		cnt = 0;
	}
	if (n >= 16)
		ft_pf_nbrlen_hex(n / 16);
	flag = 0;
	return (++cnt);
}

int	ft_pf_nbrlen_hex_addr(unsigned long long int n)
{
	static int	cnt;
	static int	flag;

	if (!flag)
	{
		flag++;
		cnt = 0;
	}
	if (n >= 16)
		ft_pf_nbrlen_hex_addr(n / 16);
	flag = 0;
	return (++cnt);
}
