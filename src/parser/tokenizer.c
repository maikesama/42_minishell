/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:48:51 by mpaci             #+#    #+#             */
/*   Updated: 2021/12/17 15:50:19 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

int	how_many_spaces(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (all->input[i])
	{
		if (all->input[i] == '\'')
			all->flag1 *= -1;
		if (all->input[i] == '"')
			all->flag2 *= -1;
		if (all->input[i] == ' ' && all->flag1 == 1 && all->flag2 == 1)
			j++;
		i++;
	}
	all->flag1 = 1;
	all->flag2 = 1;
	return (j);
}

int	ft_searchnextlen(t_all *all, int i)
{
	int	len;

	len = 0;
	while (all->input[i] != ' ' && all->input[i])
	{
		if (all->input[i] == '\'')
			all->flag1 *= -1;
		if (all->input[i] == '"')
			all->flag2 *= -1;
		len++;
		i++;
	}
	return (len);
}

void	tokenizer(t_all *all, int *j, int *i, int *x)
{
	int	len;

	len = ft_searchnextlen(all, *i);
	if ((len && all->flag1 == 1 && all->flag2 == 1))
	{
		all->tok[*j] = (char *)ft_calloc(len + 1, 1);
		if (!all->tok[*j])
			exit(EXIT_FAILURE);
		len += *i;
		while (*i < len && all->input[*i])
		{
			all->tok[*j][*x] = all->input[*i];
			*i += 1;
			*x += 1;
		}
		*j += 1;
		*x = 0;
	}
}

void	input_tok(t_all *all)
{
	int	j;
	int	i;
	int	len;
	int	x;

	len = 0;
	i = 0;
	x = 0;
	all->tok = ft_calloc(how_many_spaces(all) + 2, sizeof(*all->tok));
	if (!all->tok)
		exit(EXIT_FAILURE);
	j = 0;
	while (all->input[i] && all->input)
	{
		tokenizer(all, &j, &i, &x);
		i++;
	}
}
