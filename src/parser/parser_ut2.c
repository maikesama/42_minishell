/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ut2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:18:35 by mpaci             #+#    #+#             */
/*   Updated: 2021/12/17 16:55:14 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

int	is_spec_char(char c)
{
	int		i;
	char	*specs;

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

void	copy_spc_double(t_all *all, char **tmp, int *i, int *j)
{
	if (all->input[(*i) - 1] != ' ' && all->input[*i - 1])
	{
		tmp[0][*j] = ' ';
		*j += 1;
	}
	tmp[0][*j] = all->input[*i];
	*j += 1;
	tmp[0][*j] = all->input[*i + 1];
	*j += 1;
	if (all->input[*i + 2] != ' ' && all->input[*i + 2])
	{
		tmp[0][*j] = ' ';
		*j += 1;
	}
	*i += 1;
}

void	copy_spc_ut(t_all *all, char **tmp, int *i, int *j)
{
	if (all->input[*i - 1] != ' ' && all->input[*i - 1])
	{
		tmp[0][*j] = ' ';
		*j += 1;
	}
	tmp[0][*j] = all->input[*i];
	*j += 1;
	if (all->input[*i + 1] != ' ' && all->input[*i + 1])
	{
		tmp[0][*j] = ' ';
		*j += 1;
	}
}

void	copy_spc(t_all *all, char *tmp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (all->input[i])
	{
		copy_erase(all, &i, tmp, &j);
		if (!is_spec_char(all->input[i]))
		{
			if (all->input[i + 1] == all->input[i])
				copy_spc_double(all, &tmp, &i, &j);
			else
				copy_spc_ut(all, &tmp, &i, &j);
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
	i -= space_eraser(all->input);
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
}
