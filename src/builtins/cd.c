/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:40:50 by pceccoli          #+#    #+#             */
/*   Updated: 2022/02/05 19:11:37 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	coming_home(char *path, t_all *all)
{
	int	i;

	i = 0;
	free(path);
	while (all->mini_env[i])
	{
		if (!ft_strncmp("HOME=", all->mini_env[i], 5))
			path = ft_substr(all->mini_env[i], 5,
					ft_strlen(all->mini_env[i]) - 5);
		i++;
	}
}

void	change_pwd(t_all *all)
{
	int	i;

	i = 0;
	while (i < line_counter(all->mini_env))
	{
		if (!ft_strncmp(all->mini_env[i], "PWD=", 4))
		{
			free(all->mini_env[i]);
			all->mini_env[i] = ft_strjoin("PWD=", all->dir);
		}	
		i++;
	}
}

void	cd_error(char *str)
{
	perror(str);
	return ;
}

void	change_directory(t_all *all)
{
	char	*str;

	if (!all->tok[1] || !ft_strncmp(all->tok[1], "˜", ft_strlen(all->tok[1])))
	{
		str = malloc(1);
		coming_home(str, all);
		if (chdir((const char *)str) != 0)
			cd_error(str);
		free(str);
	}
	else
	{
		if (chdir((const char *)all->tok[1]) != 0)
			cd_error(all->tok[1]);
	}
	all->dir = getcwd(all->dir, 0);
	change_pwd(all);
	free(all->dir);
	all->dir = NULL;
	all->status = 0;
}
