/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:42:47 by mpaci             #+#    #+#             */
/*   Updated: 2021/02/01 14:42:50 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspace_bonus(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	val;
	int	sign;
	int	accumulator;

	sign = 1;
	val = 0;
	accumulator = 0;
	while (ft_isspace_bonus(((char)*str)))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
		if (*str == '+' || *str == '-')
			return (0);
	}
	while (*str >= '0' && *str <= '9' && *str)
	{
		val = (*str - '0');
		accumulator = (accumulator * 10) + val;
		str++;
	}
	return (accumulator * sign);
}
