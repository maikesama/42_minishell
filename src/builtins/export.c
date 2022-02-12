/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:45:59 by pceccoli          #+#    #+#             */
/*   Updated: 2022/02/04 19:47:54 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	re_copy_env(t_all *all, char **tmp)
{
	int	i;

	i = 0;
	all->mini_env = ft_calloc((line_counter(tmp) + 1), sizeof(*all->mini_env));
	while (tmp[i])
	{
		all->mini_env[i] = ft_calloc(ft_strlen(tmp[i]) + 1, 1);
		ft_memcpy(all->mini_env[i], tmp[i], ft_strlen(tmp[i]));
		i++;
	}
}

void	new_env(t_all *all, char *env_var)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_calloc((line_counter(all->mini_env) + 2), sizeof(*tmp));
	while (all->mini_env[i])
	{
		tmp[i] = ft_calloc(ft_strlen(all->mini_env[i]) + 1, 1);
		ft_memcpy(tmp[i], all->mini_env[i], ft_strlen(all->mini_env[i]));
		i++;
	}
	tmp[i] = ft_strjoin(env_var, "");
	free_matrix(all->mini_env);
	re_copy_env(all, tmp);
	free_matrix(tmp);
}

void	check_export(t_all *all, char *str, char *tmp)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (all->mini_env[i])
	{
		while (all->mini_env[i][j] != '=')
			j++;
		if (!ft_strncmp(all->mini_env[i], str, j))
		{
			free(all->mini_env[i]);
			all->mini_env[i] = ft_strjoin(tmp, "");
			return ;
		}
		j = 0;
		i++;
	}
	new_env(all, tmp);
}

void	ut_export(t_all *all, char *str, char *tmp)
{
	int	i;
	int	j;

	if (equal_count(all, 1))
	{
		check_export(all, str, tmp);
		free(str);
		free(tmp);
		return ;
	}
	i = 0;
	while (all->env_var && all->env_var[i]
		&& ft_strncmp(str, all->env_var[i], ft_strlen(str)))
	{
		ut_stup_two(str, all, &i, &j);
		i++;
	}
	if (j == 0)
		return ;
	if (all->env_var && all->env_var[i])
		new_env(all, all->env_var[i]);
	free(str);
	free(tmp);
}

void	export_var(t_all *all, char **mx)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	if (!mx || !mx[0])
		return ;
	if (!mx[1])
	{
		while (all->mini_env[i])
		{
			ft_printf("%s\n", all->mini_env[i]);
			i++;
		}
		return ;
	}
	while (mx[1][i] != '=' && mx[1][i])
		i++;
	str = ft_calloc(i + 1, 1);
	ft_memcpy(str, mx[1], i);
	tmp = ft_calloc(ft_strlen(mx[1]) + 1, 1);
	ft_memcpy(tmp, mx[1], ft_strlen(mx[1]));
	ut_export(all, str, tmp);
	all->status = 0;
}
