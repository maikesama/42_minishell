#include "./../../headers/main.h"

int	check_builtins(t_all *all, t_piper *piper, int cnt)
{
	ft_printf("test %d\n", cnt);
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
	{
		perror(piper[cnt].cmd);
		exit(EXIT_FAILURE);
	}
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
	{
		perror(piper[cnt].cmd);
		exit(EXIT_FAILURE);
	}
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
	{
		perror(piper[0].cmd);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
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
			if (cnt == 0)
				first_child(piper, all);
			else if (cnt != 0 && cnt != all->ops->pipe)
				next_children(piper, all, cnt);
			else if (cnt == all->ops->pipe)
				last_child(piper, all, cnt);
		}
		parent(all, cnt);
		cnt++;
	}
	ft_wait_pipe(all, id);
	return ;
}
