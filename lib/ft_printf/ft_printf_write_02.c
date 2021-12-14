/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_02.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:56:31 by mpaci             #+#    #+#             */
/*   Updated: 2021/11/08 14:56:33 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_putnbr(long int n)
{
	if (n < 0)
		ft_pf_putnbr(n * -1);
	else if (n < 10)
	{
		ft_pf_putchar(n + 48);
	}
	else if (n >= 10)
	{
		ft_pf_putnbr(n / 10);
		ft_pf_putnbr(n % 10);
	}
}

void	ft_pf_putnbr_hex(unsigned long int n)
{
	if (n >= 16)
		ft_pf_putnbr_hex(n / 16);
	if ((n % 16) > 9)
		ft_pf_putchar(87 + (n % 16));
	else
		ft_pf_putchar(48 + (n % 16));
}

void	ft_pf_putnbr_hex_up(unsigned long int n)
{
	if (n >= 16)
		ft_pf_putnbr_hex_up(n / 16);
	if ((n % 16) > 9)
		ft_pf_putchar(55 + (n % 16));
	else
		ft_pf_putchar(48 + (n % 16));
}

void	ft_pf_putnbr_hex_addr(unsigned long long int n)
{
	if (n >= 16)
		ft_pf_putnbr_hex_addr(n / 16);
	if ((n % 16) > 9)
		ft_pf_putchar(87 + (n % 16));
	else
		ft_pf_putchar(48 + (n % 16));
}
