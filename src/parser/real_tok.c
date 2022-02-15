/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_tok.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:51:36 by mpaci             #+#    #+#             */
/*   Updated: 2022/02/09 16:51:37 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

int	real_size(t_all *all, int i)
{
	int	j;
	int	cnt;

	cnt = 0;
	j = 0;
	while (all->tok[i][j])
	{
		if (all->tok[i][j] == '"' && all->flag2 == 1)
		{
			cnt++;
			all->flag1 *= -1;
		}
		else if (all->tok[i][j] == '\'' && all->flag1 == 1)
		{
			cnt++;
			all->flag2 *= -1;
		}
		j++;
	}
	return (cnt);
}

void	real_copy(t_all *all, char **tmp, int i)
{
	int	j;
	int	n;

	j = 0;
	n = 0;
	while (all->tok[i][j])
	{
		if (all->tok[i][j] == '"' && all->flag2 == 1)
		{
			j++;
			all->flag1 *= -1;
		}
		else if (all->tok[i][j] == '\'' && all->flag1 == 1)
		{
			j++;
			all->flag2 *= -1;
		}
		else
			tmp[i][n++] = all->tok[i][j++];
	}
}

void	real_tok(t_all *all)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(line_counter(all->tok) + 1, sizeof(*tmp));
	if (!tmp)
		return ;
	while (all->tok[i])
	{
		tmp[i] = ft_calloc((ft_strlen(all->tok[i]) - real_size(all, i)) + 1, 1);
		real_copy(all, tmp, i);
		i++;
	}
	free_matrix(all->tok);
	re_copy_tok(all, tmp);
	free_matrix(tmp);
}
