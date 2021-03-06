/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:45:50 by pceccoli          #+#    #+#             */
/*   Updated: 2022/02/04 19:45:54 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

int	check_var_existence(t_all *all, char **mx)
{
	int	i;

	i = 0;
	while (all->env_var && all->env_var[i])
	{
		if (!ft_strncmp(mx[1], all->env_var[i], ft_strlen(mx[1])))
			return (1);
		i++;
	}
	while (all->mini_env && all->mini_env[i])
	{
		if (!ft_strncmp(mx[1], all->mini_env[i], ft_strlen(mx[1])))
			return (1);
		i++;
	}
	return (0);
}

int	check_env_var_existence(t_all *all, char **mx)
{
	int	i;

	i = 0;
	if (!all->mini_env)
		return (0);
	while (all->mini_env[i])
	{
		if (!ft_strncmp(mx[1], all->mini_env[i], ft_strlen(mx[1])))
			return (1);
		i++;
	}
	return (0);
}

void	unset_var_var(t_all *all, char **mx)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!all->env_var)
		return ;
	tmp = ft_calloc(line_counter(all->env_var), sizeof(*tmp));
	while (all->env_var[i])
	{
		if (!ft_strncmp(mx[1], all->env_var[i], ft_strlen(mx[1])))
			i++;
		if (all->env_var[i])
		{
			tmp[j] = ft_calloc(ft_strlen(all->env_var[i]) + 1, 1);
			ft_memcpy(tmp[j], all->env_var[i], ft_strlen(all->env_var[i]));
			i++;
			j++;
		}
	}
	free_matrix(all->env_var);
	re_copy_var(all, tmp);
	free_matrix(tmp);
}

void	unset_env_var(t_all *all, char **mx)
{
	char	**tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!all->mini_env)
		return ;
	tmp = ft_calloc(line_counter(all->mini_env) + 1, sizeof(*tmp));
	while (all->mini_env[i])
	{
		if (!ft_strncmp(mx[1], all->mini_env[i], ft_strlen(mx[1])))
			i++;
		if (all->mini_env[i])
		{
			tmp[j] = ft_calloc(ft_strlen(all->mini_env[i]) + 1, 1);
			ft_memcpy(tmp[j], all->mini_env[i], ft_strlen(all->mini_env[i]));
			i++;
			j++;
		}
	}
	free_matrix(all->mini_env);
	re_copy_env(all, tmp);
	free_matrix(tmp);
}

void	unset_var(t_all *all, char **mx)
{
	if (!check_var_existence(all, mx))
		return ;
	unset_var_var(all, mx);
	if (check_env_var_existence(all, mx))
		unset_env_var(all, mx);
	all->status = 0;
}
