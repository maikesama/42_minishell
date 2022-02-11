/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ut3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:55:12 by pceccoli          #+#    #+#             */
/*   Updated: 2022/02/07 11:55:14 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"./../../headers/main.h"

int	space_eraser(t_all *all, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' && all->flag2 == 1)
			all->flag1 *= -1;
		if (str[i] == '\'' && all->flag1 == 1)
			all->flag2 *= -1;
		if (i > 0 && str[i - 1] && str[i] == ' ' && str[i - 1] == ' '
			&& all->flag1 == 1 && all->flag2 == 1)
			j++;
		i++;
	}
	return (j);
}

void	copy_erase(t_all *all, int *i, char *tmp, int *j)
{
	if (all->input[*i])
	{
		if (all->input[*i] == '"' && all->flag1 == 1)
			all->flag2 *= -1;
		if (all->input[*i] == '\'' && all->flag2 == 1)
			all->flag1 *= -1;
		if (all->input[*i + 1] && all->input[*i] == ' ' && all->input[*i + 1] == ' '
			&& all->flag1 == 1 && all->flag2 == 1)
		{
			tmp[*j] = all->input[*i];
			*j += 1;
			while (all->input[*i] == ' ')
				*i += 1;
		}
	}
}
