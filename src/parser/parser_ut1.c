/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ut1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:28:15 by mpaci             #+#    #+#             */
/*   Updated: 2022/02/07 11:53:57 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

int	check_quotes(const char *input)
{
	int	i;
	int	flag1;
	int	flag2;

	i = 0;
	flag1 = 1;
	flag2 = 1;
	while (input[i])
	{
		if (input[i] == '"' && flag2 == 1)
			flag1 *= -1;
		if (input[i] == '\'' && flag1 == 1)
			flag2 *= -1;
		i++;
	}
	if (flag1 == 1 && flag2 == 1)
		return (1);
	return (0);
}

int	spec_chars(char c)
{
	int		j;
	char	*str;

	str = "%%;()&`\\*[]#";
	j = 0;
	while (str[j] && str[j] != c)
	{
		j++;
		if (str[j] == c)
			return (0);
	}
	return (1);
}

int	check_special(t_all *all, char *str)
{
	int		i;
	int		flag1;
	int		flag2;

	i = 0;
	flag1 = 1;
	flag2 = 1;
	while (str[i] && str)
	{
		while (str[i] && str[i] != '"' && str[i] != '\'')
		{
			if (spec_chars(str[i]) == 0 && flag1 == 1 && flag2 == 1)
				return (0);
			if (str[i] == '|')
				all->ops->pipe++;
			i++;
		}
		if (str[i] == '"')
			flag1 *= -1;
		if (str[i] == '\'')
			flag2 *= -1;
		if (str[i])
			i++;
	}
	return (1);
}

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
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == spec_char)
			jeyer(str, i, &j, spec_char);
		i++;
	}
	return (j);
}
