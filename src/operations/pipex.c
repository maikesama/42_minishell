
//Work in progress...

#include "./../../headers/main.h"

void	check_redirections(t_all *all, int j)
{
	while (all->tok[j] && all->tok[j][0] != '|')
	{
		if (all->tok[j][0] == '>')
		{
			all->ops->arrow++;
			write_on_opt(all, &j);
			j--;
		}
		if (all->tok[j][0] == '<')
		{
			all->ops->worra++;
			input(all, &j);
			j--;
		}
		j++;
	}
}

int	size_matter(t_all *all, int	j)
{
	int	i;

	i = 0;
	while (all->tok[j] && all->tok[j][0] != '|')
	{
		i++;
		j++;
	}
	return (i);
}

void	args_initializer(t_all *all, t_piper *piper, int *i)
{
	int	j;

	j = *i;
	check_redirections(all, j);
	piper->args = ft_calloc(size_matter(all, j) + 1, sizeof(*piper->args));
	j = 0;
	while (all->tok[*i] && all->tok[*i][0] != '|')
	{
		piper->args[j] = ft_calloc(ft_strlen(all->tok[*i]) + 1, 1);
		ft_memcpy(piper->args[j], all->tok[*i], ft_strlen(all->tok[*i]));
		*i += 1;
		j++;
	}
}

void	free_piper(t_piper *piper, t_all *all)
{
	int	i;

	i = 0;
	free(piper->cmd);
	while (piper->args[i])
	{
		free(piper->args[i]);
		i++;
	}
	free(piper->args);
	all->ops->arrow = 0;
	all->ops->worra = 0;
	all->ops->darrow = 0;
	all->ops->dworra = 0;
}

void	last_child(t_piper *piper, t_all *all)
{
	int	i;
	int	err;

	i = 0;
	dup2(all->saved_stdout, STDOUT_FILENO);
	close(all->saved_stdout);
	dup2(piper->fd[0], STDIN_FILENO);
	close(piper->fd[0]);
	close(piper->fd[1]);
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

void	next_children(t_piper *piper, t_all *all)
{
	int	i;
	int	err;

	i = 0;
	dup2(piper->fd[1], STDOUT_FILENO);
	dup2(piper->fd[0], STDIN_FILENO);
	close(piper->fd[0]);
	close(piper->fd[1]);
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
	dup2(piper->fd[1], STDOUT_FILENO);
	close(piper->fd[0]);
	close(piper->fd[1]);
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

void	pipe_execution(t_all *all, t_piper *piper, int *cnt)
{
	pid_t	id;

	id = fork();
	if (id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (id == 0)
	{
		if (*cnt == 0)
			first_child(piper, all);
		else if (*cnt != 0 && *cnt != all->ops->pipe)
			next_children(piper, all);
		else if (*cnt == all->ops->pipe)
			last_child(piper, all);
	}
	close(piper->fd[0]);
	close(piper->fd[1]);
	waitpid(id, NULL, 0);
	return ;
}

void	pipex(t_all *all)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	t_piper	piper;

	pipe(piper.fd);
	while (all->tok[i])
	{
		piper.cmd = ft_calloc(ft_strlen(all->tok[i]) + 1, 1);
		ft_memcpy(piper.cmd, all->tok[i], ft_strlen(all->tok[i]));
		args_initializer(all, &piper, &i);
		pipe_execution(all, &piper, &cnt);
		free_piper(&piper, all);
		if (all->tok[i][0] == '|')
			i++;
		cnt++;
		ft_printf("test");
	}
}
