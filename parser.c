/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:00:00 by pceccoli          #+#    #+#             */
/*   Updated: 2021/12/17 15:19:45 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

char	*charjoin(char	*s, char c, int max)
{
	char	*ret;
	int		i;

	ret = malloc(max + 2);
	i = -1;
	while (s[++i])
		ret[i] = s[i];
	ret[i++] = c;
	ret[i] = 0;
	free(s);
	return (ret);
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
		len = ft_searchnextlen(all, i);
		if ((len && all->flag1 == 1 && all->flag2 == 1))
		{
			all->tok[j] = (char *)ft_calloc(len + 1, 1);
			if (!all->tok[j])
				exit(EXIT_FAILURE);
			len += i;
			while (i < len && all->input[i])
			{
				all->tok[j][x] = all->input[i];
				i++;
				x++;
			}
			j++;
			x = 0;
		}
		i++;
	}
	//PKpkPkPkpKkpk
}

int	parser(t_all *all)
{
	int		i;

	i = 0;
	if (!check_quotes(all->input) || !check_special(all->input))
		return (0);
	new_input(all);//add delete spaces if more than 1;
	input_tok(all);
	while (all->tok[i])
	{
		ft_printf("%s\n", all->tok[i]);
		i++;
	}
	return (1);
}
