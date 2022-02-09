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

// static void	ft_newline_sigint(int wstatus, int *newline)
// {
// 	if (WTERMSIG(wstatus) == SIGINT && *newline == 0)
// 	{
// 		*newline = *newline + 1;
// 	}
// }
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

//funzione che cerca localmente 

void	executioner_figlio(t_all *all, int i, int err)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!all->env_path || !all->env_path[0])
	{
		ft_printf("%s: No such file or directory\n", all->tok[0]);
		exit(EXIT_FAILURE);
	}
	all->cmd = all->tok[0];
	execve(all->cmd, all->tok, all->mini_env);
	while (all->env_path && all->env_path[i])
	{
		all->cmd = all->tok[0];
		all->cmd = ft_strjoin(all->env_path[i], all->tok[0]);
		err = execve(all->cmd, all->tok, all->mini_env);
		free(all->cmd);
		i++;
	}
	if (err == -1)
	{
		perror(all->tok[0]);
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
		executioner_figlio(all, i, err);
	ft_wait(all, id);
	return ;
}
