/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_03.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:56:24 by mpaci             #+#    #+#             */
/*   Updated: 2021/11/08 14:56:26 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_width_write(t_struct *fl, int len)
{
	while (fl->width > len)
	{
		ft_pf_putchar(' ');
		fl->cnt++;
		fl->width--;
	}
}

void	ft_pf_precision_write(t_struct *fl)
{
	while ((fl->prc) > 0)
	{
		ft_pf_putchar('0');
		fl->cnt++;
		fl->prc--;
	}
}

void	ft_pf_zero_write(t_struct *fl, int len)
{
	while (fl->zero > len)
	{
		ft_pf_putchar('0');
		fl->cnt++;
		fl->zero--;
	}
}

void	ft_pf_minus_write(t_struct *fl, long int n)
{
	if (n < 0)
	{
		fl->cnt++;
		ft_pf_putchar('-');
	}
}

int	ft_pf_exist_write(long int n, int len, t_struct *fl)
{
	if (!n && !fl->prc)
	{
		len--;
		if (fl->zero)
			fl->width = fl->zero;
		ft_pf_width_write(fl, len);
		return (0);
	}
	else
		return (1);
}
