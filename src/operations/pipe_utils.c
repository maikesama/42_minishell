/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:51:59 by mpaci             #+#    #+#             */
/*   Updated: 2022/02/09 16:52:00 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	err_pipe_exec(t_piper *piper, int cnt)
{
	perror(piper[cnt].cmd);
	exit(EXIT_FAILURE);
}

void	parent(t_all *all, int cnt)
{
	if (cnt == 0)
		close(all->fd[0][1]);
	else if (cnt != 0 && cnt != all->ops->pipe)
	{
		close(all->fd[cnt - 1][0]);
		close(all->fd[cnt][1]);
	}
	else
	{
		close(all->fd[cnt - 1][0]);
		close(all->fd[cnt][1]);
		close(all->fd[cnt][0]);
	}
	reset_in_out(all);
}

void	pipe_execution(t_all *all, t_piper *piper)
{
	pid_t	*id;
	int		cnt;

	cnt = 0;
	id = malloc((all->ops->pipe + 2) * sizeof(*id));
	signal(SIGINT, SIG_IGN);
	while (cnt <= all->ops->pipe)
	{
		id[cnt] = fork();
		if (id[cnt] == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (id[cnt] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			child_launcher(piper, all, cnt);
		}
		parent(all, cnt);
		cnt++;
	}
	ft_wait_pipe(all, id);
	return ;
}
