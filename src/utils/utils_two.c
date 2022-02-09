/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:51:36 by mpaci             #+#    #+#             */
/*   Updated: 2022/02/09 16:51:37 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	ut_stup_two(char *str, t_all *all, int *i, int *j)
{
	if (ft_strncmp(str, all->env_var[*i], ft_strlen(str)))
		*j = 0;
	else
		*j = 1;
}

void	take_path(t_all *all)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	while (all->mini_env && all->mini_env[i])
	{
		if (!ft_strncmp(all->mini_env[i], "PATH=", 5))
		{
			ret = 1;
			get_path(all->mini_env[i], all);
		}
		i++;
	}
	if (ret == 0)
		all->env_path = ft_calloc(1, sizeof(all->env_path));
}

void	ut_stupx(char **mx)
{
	ft_printf("exit: %s: numeric argument required\n",
		mx[1]);
}

int	exit_error(t_all *all, char **mx)
{
	int	i;

	i = 0;
	if (mx && mx[0][0])
	{
		if (mx && mx[1] && mx[1][0])
		{
			if (mx[2])
			{
				ft_printf("exit: too many arguments\n");
				return (1);
			}	
			while (mx[1][i])
			{
				if (!ft_isdigit(mx[1][i]))
				{
					ut_stupx(mx);
					return (1);
				}
				i++;
			}
			all->status = ft_atoi(mx[1]);
		}
	}
	return (0);
}

void	set_in_out(t_all *all)
{
	if (all->ops->arrow)
	{
		dup2(all->fd_out, STDOUT_FILENO);
		close(all->fd_out);
	}
	if (all->ops->worra)
	{
		if (all->ops->dworra)
			all->fd_in = open("/tmp/file.txt", O_RDONLY);
		dup2(all->fd_in, STDIN_FILENO);
		close(all->fd_in);
	}
}
