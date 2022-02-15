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

void	child_check(t_all *all, t_piper *piper, int cnt)
{
	if (piper[cnt].cmd && piper[cnt].cmd[0] && ((piper[cnt].cmd[0] == '.'
				&& piper[cnt].cmd[1] == '/') || piper[cnt].cmd[0] == '/'))
		execve(piper[cnt].cmd, piper[cnt].args, all->mini_env);
	if (check_builtins(all, piper, cnt))
		exit(all->status);
	if (!all->env_path || !all->env_path[0])
	{
		ft_printf("%s: No such file or directory\n", all->tok[0]);
		exit(EXIT_FAILURE);
	}
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
	child_check(all, piper, cnt);
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
	child_check(all, piper, cnt);
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
	child_check(all, piper, 0);
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
