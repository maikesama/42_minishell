/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:45:00 by pceccoli          #+#    #+#             */
/*   Updated: 2022/02/05 20:18:01 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	ft_wait(t_all *all, pid_t id)
{
	int	wexit;
	int	status;

	wexit = waitpid(id, &status, WUNTRACED);
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
} 

void	do_your_job_son(t_all *all, int i, int err)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (all->tok && all->tok[0] && all->tok[0][0] && ((all->tok[0][0] == '.'
		&& all->tok[0][1] == '/') || all->tok[0][0] == '/' || !ft_strncmp(all->tok[0], "make", ft_strlen(all->tok[0]))))
	{
		all->cmd = ft_calloc(ft_strlen(all->tok[0]) + 1, 1);
		ft_memcpy(all->cmd, all->tok[0], ft_strlen(all->tok[0]));
		execve(all->cmd, all->tok, all->mini_env);
	}
	if (!all->env_path || !all->env_path[0])
	{
		ft_printf("%s: No such file or directory\n", all->tok[0]);
		exit(EXIT_FAILURE);
	}
	while (all->env_path && all->env_path[i])
	{
		all->cmd = ft_strjoin(all->env_path[i], all->tok[0]);
		err = execve(all->cmd, all->tok, all->mini_env);
		free(all->cmd);
		i++;
	}
	if (err == -1)
	{
		ft_printf("%s: command not found\n", all->tok[0]);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	executioner(t_all *all)
{
	int		i;
	int		err;
	pid_t	id;

	i = 0;
	err = 0;
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (id == 0)
		do_your_job_son(all, i, err);
	ft_wait(all, id);
	return ;
}
