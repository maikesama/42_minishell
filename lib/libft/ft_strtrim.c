/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:13:51 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/27 15:13:53 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_charset(char c, char *charset)
{
	t_size	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *s2)
{
	char	*s;
	t_size	start;
	t_size	end;
	t_size	i;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen((char *)s1);
	while (s1[start] && is_in_charset(s1[start], (char *)s2))
		start++;
	while (end > start && is_in_charset(s1[end - 1], (char *)s2))
		end--;
	s = (char *)malloc((end - start + 1) * sizeof(char));
	i = 0;
	while (start < end)
		s[i++] = s1[start++];
	s[i] = '\0';
	return (s);
}
