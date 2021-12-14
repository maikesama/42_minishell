/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:50:06 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/28 14:50:09 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_rows(char const *s, char c)
{
	t_size		i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (i + 1);
}

int	check(char **matrix, int p)
{
	if (!matrix[p])
	{
		while (p)
		{
			p--;
			free(matrix[p]);
		}
		free(matrix);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char		**res;
	char		*start;
	t_size		i;
	t_size		len;

	res = (char **)ft_calloc(ft_count_rows(s, c), sizeof(char *));
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			start = (char *)s;
			while (*s && *s != c)
				s++;
			len = s - start + 1;
			res[i] = (char *)malloc(len);
			if (!(check(res, i)))
				return (0);
			ft_strlcpy(res[i++], start, len);
		}
		else
			s++;
	}
	return (res);
}
