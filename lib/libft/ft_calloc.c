/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:21:01 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/20 18:21:04 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!size)
	{
		ptr = malloc(size);
		return (ptr);
	}
	ptr = malloc(size * count);
	ft_bzero(ptr, size * count);
	return (ptr);
}
