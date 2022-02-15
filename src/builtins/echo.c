/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:41:55 by pceccoli          #+#    #+#             */
/*   Updated: 2022/02/05 19:13:05 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	echo_just_for_norm(t_all *all, int i, int *j)
{
	while (all->tok && all->tok[i] && all->tok[i][*j])
	{
		if (all->tok[i] && all->tok[i][*j])
		{
			write(1, &all->tok[i][*j], 1);
			*j += 1;
		}
	}
}

void	skip_flags(t_all *all, int *i)
{
	int	f;
	int	j;

	f = 0;
	j = 2;
	while (all->tok[*i] && all->tok[*i][0] &&
		!ft_strncmp(all->tok[*i], "-n", 2))
	{
		while (all->tok[*i][j])
		{
			if (all->tok[*i][j] != 'n')
			{
				f = 1;
				break ;
			}
			j++;
		}
		if (f == 1)
			break ;
		j = 2;
		all->echoflag = 1;
		if (all->tok[*i][0])
			*i += 1;
	}
}

void	echo(t_all *all)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!all->tok[1])
	{
		write(1, "\n", 1);
		return ;
	}
	skip_flags(all, &i);
	if (!all->tok[i])
		return ;
	while (all->tok[i])
	{
		echo_just_for_norm(all, i, &j);
		if (all->tok && all->tok[i] && all->tok[i + 1] && all->tok[i + 1][0])
			write(1, " ", 1);
		j = 0;
		i++;
	}
	if (all->echoflag == 0)
		ft_printf("\n");
	else if (all->echoflag == 1)
		all->echoflag = 0;
	all->status = 0;
}
