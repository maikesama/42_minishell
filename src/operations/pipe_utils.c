#include "./../../headers/main.h"

void	last_child(t_piper *piper, t_all *all, int cnt)
{
	int	i;
	int	err;

	i = 0;
	dup2(all->saved_stdout, STDOUT_FILENO);
	close(all->saved_stdout);
	dup2(piper->fd[cnt - 1][0], STDIN_FILENO);
	close(piper->fd[cnt - 1][0]);
	close(piper->fd[cnt][0]);
	close(piper->fd[cnt][1]);
	set_in_out(all);
	while (all->env_path[i])
	{
		all->cmd = ft_strjoin(all->env_path[i], piper->cmd);
		err = execve(all->cmd, piper->args, all->mini_env);
		free(all->cmd);
		i++;
	}
	if (err == -1)
	{
		perror(piper->cmd);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	next_children(t_piper *piper, t_all *all, int cnt)
{
	int	i;
	int	err;

	i = 0;
	dup2(piper->fd[cnt - 1][0], STDIN_FILENO);
	dup2(piper->fd[cnt][1], STDOUT_FILENO);
	close(piper->fd[cnt - 1][0]);
	close(piper->fd[cnt][1]);
	set_in_out(all);
	while (all->env_path[i])
	{
		all->cmd = ft_strjoin(all->env_path[i], piper->cmd);
		err = execve(all->cmd, piper->args, all->mini_env);
		free(all->cmd);
		i++;
	}
	if (err == -1)
	{
		perror(piper->cmd);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	first_child(t_piper *piper, t_all *all)
{
	int	i;
	int	err;

	i = 0;
	dup2(piper->fd[0][1], STDOUT_FILENO);
	close(piper->fd[0][0]);
	close(piper->fd[0][1]);
	set_in_out(all);
	while (all->env_path[i])
	{
		all->cmd = ft_strjoin(all->env_path[i], piper->cmd);
		err = execve(all->cmd, piper->args, all->mini_env);
		free(all->cmd);
		i++;
	}
	if (err == -1)
	{
		perror(piper->cmd);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

void	parent(t_piper *piper, t_all *all, int *cnt)
{
	if (*cnt == 0)
			close(piper->fd[0][1]);
	else if (*cnt != 0 && *cnt != all->ops->pipe)
	{
		close(piper->fd[*cnt - 1][0]);
		close(piper->fd[*cnt][1]);
	}
	else
	{
		close(piper->fd[*cnt - 1][0]);
		close(piper->fd[*cnt][1]);
		close(piper->fd[*cnt][0]);
	}
	reset_in_out(all);
}

void	pipe_execution(t_all *all, t_piper *piper, int *cnt)
{
	pid_t	id;

	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (*cnt == 0)
			first_child(piper, all);
		else if (*cnt != 0 && *cnt != all->ops->pipe)
			next_children(piper, all, *cnt);
		else if (*cnt == all->ops->pipe)
			last_child(piper, all, *cnt);
	}
	else
	{
		parent(piper, all, cnt);
		ft_wait(all, id);
	}
	return ;
}
