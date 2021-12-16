/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:00:00 by pceccoli          #+#    #+#             */
/*   Updated: 2021/12/16 14:28:38 by mpaci            ###   ########.fr       */
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

void	input_tok(t_all *all)
{
	int	j;
	int	i;
	int	len;
	int	start;

	len = 0;
	i = 0;
	start = 0;
	all->tok = (char **)ft_calloc(how_many_spaces(all) + 2, sizeof(char *));
	j = 0;
	while (all->input[i] && all->input)
	{
		while (all->input[i] != ' ' && all->input[i])
		{
			if (all->input[i] == '\'')
				all->flag1 *= -1;
			if (all->input[i] == '"')
				all->flag2 *= -1;
			len++;
			i++;
		}
		if ((all->input[i] == '\0' || all->input[i] == ' ') && all->flag1 == 1 && all->flag2 == 1)
		{
			all->tok[j] = (char *)ft_calloc(len + 1, 1);
			while (start < (start + len) && all->input[start])
			{
				all->tok[j][start] = all->input[start];
				start++;
			}
			j++;
			start++;
			len = 0;
			ft_printf("%d\n",j);
		}
		i++;
	}
}

int	parser(t_all *all)
{
	int		i;

	i = 0;
	if (!check_quotes(all->input) || !check_special(all->input))
		return (0);
	new_input(all);//add delete spaces if more than 1 && add spaces for "" and  '';
	input_tok(all);//debug
	while (all->tok[i])
	{
		printf("%s\n", all->tok[i]);
		i++;
	}
	return (1);
}
