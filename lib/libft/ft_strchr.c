/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 15:14:58 by mpaci             #+#    #+#             */
/*   Updated: 2021/01/12 15:15:02 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int c)
{
	char	flag;

	flag = c;
	while (*str && *str != flag)
	{
		str++;
	}
	if (*str == flag)
		return ((char *)(str));
	else if (flag == '\0')
		return ((char *)(str + 1));
	return (0);
}
