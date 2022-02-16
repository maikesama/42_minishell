/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:51:36 by mpaci             #+#    #+#             */
/*   Updated: 2022/02/09 16:51:37 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

int	exit_var(t_all *all)
{
	char	*str;
	int		j;

	str = ft_itoa(all->status);
	j = ft_strlen(str);
	free(str);
	return (j);
}

int	check_var_len(t_all *all, int j, int mode)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	all->mode = mode;
	if (mode == 0)
	{
		while (all->mini_env[j][i] && all->mini_env[j][i] != '=')
			i++;
		while (all->mini_env[j][i + len])
			len++;
		return (len);
	}
	else if (mode == 1)
	{
		while (all->env_var[j][i] && all->env_var[j][i] != '=')
			i++;
		while (all->env_var[j][i + len])
			len++;
		return (len);
	}
	return (0);
}

int	where_is_it(t_all *all)
{
	int	len;

	len = 0;
	while (all->mini_env && all->mini_env[all->pos])
	{
		while (all->mini_env[all->pos][len]
			&& all->mini_env[all->pos][len] != '=')
			len++;
		if (!ft_strncmp(all->str, all->mini_env[all->pos], len))
			return (check_var_len(all, all->pos, 0));
		len = 0;
		all->pos++;
	}
	all->pos = 0;
	while (all->env_var && all->env_var[all->pos])
	{
		while (all->env_var[all->pos][len]
			&& all->env_var[all->pos][len] != '=')
			len++;
		if (!ft_strncmp(all->str, all->env_var[all->pos], len))
			return (check_var_len(all, all->pos, 1));
		len = 0;
		all->pos++;
	}
	return (0);
}

int	variable_found(t_all *all, int i)
{
	int		j;
	int		len;

	j = 0;
	i++;
	while (all->input[i + j] && all->input[i + j] != ' '
		&& all->input[i + j] != '"' && all->input[i + j] != '\'')
		j++;
	all->str = ft_substr(all->input, i, j);
	if (!ft_strncmp(all->str, "?", ft_strlen(all->str)))
		return (exit_var(all));
	all->pos = 0;
	len = where_is_it(all);
	if (len > 0)
		return (len);
	free(all->str);
	return (0);
}

void	input_expand(t_all *all)
{
	int	i;
	int	len;

	i = 0;
	while (all->input && all->input[i])
	{
		if (all->input[i] == '"' && all->flag2 == 1)
			all->flag1 *= -1;
		if (all->input[i] == '\'' && all->flag1 == 1)
			all->flag2 *= -1;
		if (all->input[i] == '$' && all->flag2 == 1)
		{
			len = variable_found(all, i);
			if (!input_expand_ut(all, &i, len))
			{
				delete_var(all, i);
				if (!all->input || !all->input[i])
					break ;
				if (i > 0)
					i -= 1;
			}
		}
		i++;
	}
}
