/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_expand_ut.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:51:36 by mpaci             #+#    #+#             */
/*   Updated: 2022/02/09 16:51:37 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	expanding_var2(t_all *all, char *tmp, int *n, int *j)
{
	while (all->env_var[all->pos][*j] && all->env_var[all->pos][*j] != '=')
		*j += 1;
	*j += 1;
	while (all->env_var[all->pos][*j])
	{
		tmp[*n] = all->env_var[all->pos][*j];
		*j += 1;
		*n += 1;
	}
}

void	expanding_var(t_all *all, char *tmp, int *n, int *j)
{
	if (!ft_strncmp(all->str, "?", ft_strlen(all->str)))
		expand_exit(all, tmp, n);
	else if (all->mode == 0)
	{
		while (all->mini_env[all->pos][*j]
			&& all->mini_env[all->pos][*j] != '=')
			*j += 1;
		*j += 1;
		while (all->mini_env[all->pos][*j])
		{
			tmp[*n] = all->mini_env[all->pos][*j];
			*j += 1;
			*n += 1;
		}
	}
	else if (all->mode == 1)
		expanding_var2(all, tmp, n, j);
}

void	copy_var(t_all *all, int i, int len)
{
	char	*tmp;
	int		j;
	int		n;

	j = 0;
	n = i + 1;
	while (all->input[n] && all->input[n] != ' ' && all->input[n] != '"'
		&& all->input[n] != '\'')
	{
		n++;
		j++;
	}
	tmp = ft_calloc((ft_strlen(all->input) + len - j) + 1, 1);
	ft_memcpy(tmp, all->input, i);
	n = i;
	i += j + 1;
	j = 0;
	expanding_var(all, tmp, &n, &j);
	while (all->input[i])
		tmp[n++] = all->input[i++];
	free(all->input);
	all->input = ft_calloc(ft_strlen(tmp) + 1, 1);
	ft_memcpy(all->input, tmp, ft_strlen(tmp));
	free(tmp);
	free(all->str);
}

void	delete_var(t_all *all, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	while (all->input[i + j] && all->input[i + j] != ' '
		&& all->input[i + j] != '"' && all->input[i + j] != '\'')
		j++;
	tmp = ft_calloc((ft_strlen(all->input) - j) + 1, 1);
	j += i;
	ft_memcpy(tmp, all->input, i);
	while (all->input[j])
		tmp[i++] = all->input[j++];
	free(all->input);
	all->input = ft_calloc(ft_strlen(tmp) + 1, 1);
	ft_memcpy(all->input, tmp, ft_strlen(tmp));
	free(tmp);
}

int	input_expand_ut(t_all *all, int *i, int len)
{
	if (len > 0)
	{
		copy_var(all, *i, len);
		*i -= 1;
		return (1);
	}
	return (0);
}
