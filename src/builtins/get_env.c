/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:45:29 by pceccoli          #+#    #+#             */
/*   Updated: 2022/02/04 19:47:29 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

int	line_counter(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

void	get_path(char *path_line, t_all *all)
{
	int		i;
	char	**tmp;
	char	*str;

	i = 0;
	str = ft_substr(path_line, 5, ft_strlen(path_line) - 5);
	all->env_path = ft_split(str, ':');
	free(str);
	tmp = ft_calloc(line_counter(all->env_path) + 1, sizeof(*tmp));
	while (all->env_path[i])
	{
		tmp[i] = ft_strjoin(all->env_path[i], "/");
		i++;
	}
	free_matrix(all->env_path);
	i = 0;
	all->env_path = ft_calloc(line_counter(tmp) + 1, sizeof(*all->env_path));
	while (tmp[i])
	{
		all->env_path[i] = ft_calloc(ft_strlen(tmp[i]) + 1, 1);
		ft_memcpy(all->env_path[i], tmp[i], ft_strlen(tmp[i]));
		i++;
	}
	free_matrix(tmp);
}

void	print_env(t_all *all)
{
	int	i;

	i = 0;
	while (all->mini_env[i])
	{
		ft_printf("%s\n", all->mini_env[i]);
		i++;
	}
}

void	next_level(t_all *all, char **env, int i)
{
	char	*str;
	int		n;

	str = ft_substr(env[i], 6, ft_strlen(env[i] - 6));
	n = ft_atoi(str);
	n += 1;
	free(str);
	str = ft_itoa(n);
	all->mini_env[i] = ft_strjoin("SHLVL=", str);
	free(str);
}

void	get_env(t_all *all, char **env)
{
	int	i;

	i = 0;
	all->mini_env = ft_calloc(line_counter(env) + 1, sizeof(*all->mini_env));
	while (env[i])
	{
		if (!ft_strncmp(env[i], "SHLVL=", 6))
		{
			next_level(all, env, i);
			i++;
		}
		else
		{
			all->mini_env[i] = ft_calloc(ft_strlen(env[i]) + 1, 1);
			ft_memcpy(all->mini_env[i], env[i], ft_strlen(env[i]));
			i++;
		}
	}
}
