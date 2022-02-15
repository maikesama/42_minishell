/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:45:20 by pceccoli          #+#    #+#             */
/*   Updated: 2022/02/04 19:45:24 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

// int	try_to_find_on_var(t_all *all, char *str)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	while (all->env_var[i])
// 	{
// 		while (all->env_var[i][j] != '=' && all->env_var[i][j])
// 			j++;
// 		if (!ft_strncmp(str, all->env_var[i], j))
// 			return (1);
// 		j = 0;
// 		i++;
// 	}
// 	return (0);
// }

// int	is_var(t_all *all, char *str)
// {
// 	int	i;
// 	int	j;

// 	j = 0;
// 	i = 0;
// 	if (all->env_var && all->env_var[0])
// 	{
// 		if (try_to_find_on_var(all, str) == 1)
// 			return (1);
// 	}
// 	while (i < line_counter(all->mini_env))
// 	{
// 		while (all->mini_env[i][j] != '=' && all->mini_env[i][j] != 0
// 			&& all->mini_env[i] && all->mini_env)
// 				j++;
// 		if (!ft_strncmp(str, all->mini_env[i], j))
// 			return (1);
// 		j = 0;
// 		i++;
// 	}
// 	return (0);
// }

// int	write_var_from_env(t_all *all, char *str)
// {
// 	int	i;
// 	int	l;
// 	int	ret;

// 	ret = 0;
// 	i = 0;
// 	l = 0;
// 	while (all->mini_env[i])
// 	{
// 		while (all->mini_env[i][l] != '=')
// 			l++;
// 		if (!ft_strncmp(str, all->mini_env[i], l))
// 		{
// 			ret = 1;
// 			l++;
// 			while (all->mini_env[i][l])
// 			{
// 				write(1, &all->mini_env[i][l], 1);
// 				l++;
// 			}
// 		}
// 		l = 0;
// 		i++;
// 	}
// 	return (ret);
// }

// void	write_var(t_all *all, char *str)
// {
// 	int	i;
// 	int	l;

// 	i = 0;
// 	l = 0;
// 	if (write_var_from_env(all, str))
// 		return ;
// 	while (all->env_var[i])
// 	{
// 		while (all->env_var[i][l] != '=')
// 			l++;
// 		if (!ft_strncmp(str, all->env_var[i], l))
// 		{
// 			l++;
// 			while (all->env_var[i][l])
// 			{
// 				write(1, &all->env_var[i][l], 1);
// 				l++;
// 			}
// 		}
// 		l = 0;
// 		i++;
// 	}
// }
