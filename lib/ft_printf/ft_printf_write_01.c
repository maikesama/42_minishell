/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_write_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:56:38 by mpaci             #+#    #+#             */
/*   Updated: 2021/11/08 14:56:40 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pf_putchar(char c)
{
	write(1, &c, sizeof(c));
}

void	ft_pf_putstr(char *s)
{
	if (s)
	{
		while (*s)
		{
			write(1, s, sizeof(*s));
			s++;
		}
	}
}

void	ft_pf_putstrlen(char *s, int len)
{
	if (s)
	{
		while (len && *s)
		{
			write(1, s, sizeof(*s));
			s++;
			len--;
		}
	}
}
