/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:00:00 by pceccoli          #+#    #+#             */
/*   Updated: 2021/12/14 18:43:59 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	jeyer(char	*str, int i, int *j, char spec_char)
{
	if (str[i + 1] == spec_char)
	{
		if (str[i - 1] != ' ')
			*j += 1;
		if (str[i + 2] != ' ')
			*j += 1;
		i++;
	}
	else
	{
		if (str[i - 1] != ' ')
			*j += 1;
		if (str[i + 1] != ' ')
			*j += 1;
	}
}

int	add_spaces(char *str, char spec_char)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if (str[i] == spec_char)
			jeyer(str, i, &j, spec_char);
		i++;
	}
	return (j);
}

int is_spec_char(char c)
{
	int i;
	char *specs;

	specs = "<>|";
	i = 0;
	while (specs[i])
	{
		if (c == specs[i])
			return (0);
		i++;
	}
	return (1);
}

void	copy_spc(t_all *all, char *tmp) //copy + spaces = new_input;
{
	int 	i;
	int		j;

	i = 0;
	j = 0;
	while (all->input[i])
	{
		if (!is_spec_char(all->input[i]))
		{
			if (all->input[i + 1] == all->input[i])
			{
				if (all->input[i - 1] != ' ')
				{
					tmp[j] = ' ';
					j++;
				}
				tmp[j] = all->input[i];
				j++;
				tmp[j] = all->input[i + 1];
				j++;
				if (all->input[i + 2] != ' ')
				{
					tmp[j] = ' ';
					j++;
				}
				i++;
			}
			else
			{
				if (all->input[i - 1] != ' ' && all->input[i - 1])
				{
					tmp[j] = ' ';
					j++;
				}
				tmp[j] = all->input[i];
				j++;
				if (all->input[i + 1] != ' ' && all->input[i + 1])
				{
					tmp[j] = ' ';
					j++;
				}
			}
			i++;
		}
		tmp[j++] = all->input[i++];
	}
}

void	new_input(t_all *all)
{
	char	*check;
	char	*tmp;
	int		j;
	int		i;

	i = 0;
	check = "<>|";
	j = 0;
	while (check[j])
	{
		i += add_spaces(all->input, check[j]);
		j++;
	}
	tmp = ft_calloc(ft_strlen(all->input) + i + 1, 1);
	copy_spc(all, tmp);
	all->input = ft_realloc(all->input, ft_strlen(tmp) + 1);
	all->input[ft_strlen(tmp) + 1] = 0;
	j = 0;
	while (tmp[j])
	{
		all->input[j] = tmp[j];
		j++;
	}
	free(tmp);
	printf("%s\n", all->input);
}

int	parser(t_all *all)
{
	int		i;

	i = 0;
	if (!check_quotes(all->input) || !check_special(all->input))
		return (0);

	new_input(all);
	return (1);	
}
