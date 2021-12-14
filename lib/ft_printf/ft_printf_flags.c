/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:57:18 by mpaci             #+#    #+#             */
/*   Updated: 2021/11/08 14:57:20 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_pf_flag_pad(char *str, t_struct *fl)
{
	fl->pad = 1;
	str++;
	return (str);
}

char	*ft_pf_flag_zero(char *str, t_struct *fl, va_list args)
{
	str++;
	if (*str == '*')
	{
		fl->zero = va_arg(args, int);
		if (fl->zero < 0)
		{
			fl->width = fl->zero * -1;
			fl->pad = 1;
			fl->zero = 0;
		}
		str++;
	}
	else
	{
		fl->zero = ft_pf_atoi(str);
		while (ft_pf_isdigit(*str))
			str++;
	}
	return (str);
}

char	*ft_pf_flag_width(char *str, t_struct *fl)
{
	fl->width = ft_pf_atoi(str);
	while (ft_pf_isdigit(*str))
		str++;
	return (str);
}

char	*ft_pf_flag_arg(char *str, t_struct *fl, va_list args)
{
	fl->width = va_arg(args, int);
	if (fl->width < 0)
	{
		fl->width *= -1;
		fl->pad = 1;
	}
	str++;
	return (str);
}

char	*ft_pf_flag_prc(char *str, t_struct *fl, va_list args)
{
	str++;
	if (*str == '*')
	{
		fl->prc = va_arg(args, int);
		str++;
	}
	else
	{
		fl->prc = ft_pf_atoi(str);
		while (ft_pf_isdigit(*str))
			str++;
	}
	return (str);
}
