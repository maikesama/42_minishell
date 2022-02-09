/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:51:43 by mpaci             #+#    #+#             */
/*   Updated: 2022/02/09 16:51:44 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	free_matrix(char **mx)
{
	int	i;

	i = 0;
	if (!mx)
		return ;
	else
	{
		while (mx && mx[i])
		{
			free(mx[i]);
			i++;
		}
		free(mx);
	}
}

int	check_existence_env(t_all *all)
{
	char	*str;
	int		i;

	i = 0;
	if (!all->mini_env)
		return (-1);
	while (all->tok[0][i] != '=')
		i++;
	str = ft_calloc(i + 1, 1);
	ft_memcpy(str, all->tok[0], i);
	i = 0;
	while (all->mini_env[i])
	{
		if (!ft_strncmp(str, all->mini_env[i], ft_strlen(str)))
			return (i);
		i++;
	}
	free(str);
	return (-1);
}

int	check_existence_var(t_all *all)
{
	char	*str;
	int		i;

	i = 0;
	if (!all->env_var)
		return (-1);
	while (all->tok[0][i] != '=')
		i++;
	str = ft_calloc(i + 1, 1);
	ft_memcpy(str, all->tok[0], i);
	i = 0;
	while (all->env_var[i])
	{
		if (!ft_strncmp(str, all->env_var[i], ft_strlen(str)))
			return (i);
		i++;
	}
	free(str);
	return (-1);
}

void	ft_wait_pipe(t_all *all, pid_t *id)
{
	int	wexit;
	int	status;
	int	i;

	i = 0;
	while (i <= all->ops->pipe)
	{
		wexit = waitpid(id[i], &status, WUNTRACED);
		if (wexit == -1)
			perror("waitpid");
		if (WIFSTOPPED(status))
			all->status = WSTOPSIG(status) + 128;
		if (WIFSIGNALED(status))
		{
			ft_printf("\n");
			all->status = WTERMSIG(status) + 128;
		}
		if (WIFEXITED(status))
			all->status = WEXITSTATUS(status);
		i++;
	}
}
