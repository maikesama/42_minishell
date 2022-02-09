/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:08:23 by mpaci             #+#    #+#             */
/*   Updated: 2022/02/09 17:08:24 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

int	check_builtins(t_all *all, t_piper *piper, int cnt)
{
	if (!ft_strncmp(piper[cnt].cmd, "export", ft_strlen(piper[cnt].cmd)))
	{
		export_var(all, piper[cnt].args);
		return (1);
	}
	else if (!ft_strncmp(piper[cnt].cmd, "exit", ft_strlen(piper[cnt].cmd)))
	{
		exit_error(all, piper[cnt].args);
		return (1);
	}
	else if (!ft_strncmp(piper[cnt].cmd, "unset", ft_strlen(piper[cnt].cmd)))
	{
		unset_var(all, piper[cnt].args);
		return (1);
	}
	return (0);
}

void	last_child(t_piper *piper, t_all *all, int cnt)
{
	int	i;
	int	err;

	i = 0;
	dup2(all->saved_stdout, STDOUT_FILENO);
	close(all->saved_stdout);
	dup2(all->fd[cnt - 1][0], STDIN_FILENO);
	close(all->fd[cnt - 1][0]);
	close(all->fd[cnt][0]);
	close(all->fd[cnt][1]);
	set_in_out(all);
	if (check_builtins(all, piper, cnt))
		exit(all->status);
	while (all->env_path[i])
	{
		all->cmd = ft_strjoin(all->env_path[i], piper[cnt].cmd);
		err = execve(all->cmd, piper[cnt].args, all->mini_env);
		free(all->cmd);
		i++;
	}
	if (err == -1)
		err_pipe_exec(piper, cnt);
	exit(EXIT_SUCCESS);
}

void	next_children(t_piper *piper, t_all *all, int cnt)
{
	int	i;
	int	err;

	i = 0;
	dup2(all->fd[cnt - 1][0], STDIN_FILENO);
	dup2(all->fd[cnt][1], STDOUT_FILENO);
	close(all->fd[cnt - 1][0]);
	close(all->fd[cnt][1]);
	set_in_out(all);
	if (check_builtins(all, piper, cnt))
		exit(all->status);
	while (all->env_path[i])
	{
		all->cmd = ft_strjoin(all->env_path[i], piper[cnt].cmd);
		err = execve(all->cmd, piper[cnt].args, all->mini_env);
		free(all->cmd);
		i++;
	}
	if (err == -1)
		err_pipe_exec(piper, cnt);
	exit(EXIT_SUCCESS);
}

void	first_child(t_piper *piper, t_all *all)
{
	int	i;
	int	err;

	i = 0;
	dup2(all->fd[0][1], STDOUT_FILENO);
	close(all->fd[0][0]);
	close(all->fd[0][1]);
	set_in_out(all);
	if (check_builtins(all, piper, 0))
		exit(all->status);
	while (all->env_path[i])
	{
		all->cmd = ft_strjoin(all->env_path[i], piper[0].cmd);
		err = execve(all->cmd, piper[0].args, all->mini_env);
		free(all->cmd);
		i++;
	}
	if (err == -1)
		err_pipe_exec(piper, 0);
	exit(EXIT_SUCCESS);
}

void	child_launcher(t_piper *piper, t_all *all, int cnt)
{
	if (cnt == 0)
		first_child(piper, all);
	else if (cnt != 0 && cnt != all->ops->pipe)
		next_children(piper, all, cnt);
	else if (cnt == all->ops->pipe)
		last_child(piper, all, cnt);
}
