/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:33:54 by mpaci             #+#    #+#             */
/*   Updated: 2021/12/10 15:08:42 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;

	if (!(s1) || !(s2))
		return (0);
	ptr = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	ft_memmove(ptr, s1, ft_strlen(s1));
	ft_memmove(&ptr[ft_strlen(s1)], s2, ft_strlen(s2));
	return (ptr);
}
