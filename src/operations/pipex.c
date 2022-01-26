
//Work in progress...

#include "./../../headers/main.h"

int	args_cnt(char **tok, int n)
{
	int	i;

	i = 0;
	if (tok[n][0] == '|')
		n++;
	while (tok[n][0] != '|' && tok[n] && tok[n][0] && tok)
	{
		n++;
		i++;
	}
	return (i);
}

void	free_piper(t_piper *piper)
{
	int	i;

	i = 0;
	if (piper->cmd && piper->cmd[0])
		free_matrix(piper->cmd);
	while (piper->args[i] && piper->args[i][0])
	{
		free_matrix(piper->args[i]);
		i++;
	}
}

void	args_copy(t_all *all, t_piper *piper, int *j, int n)
{
	int	i;

	i = 0;
	while (all->tok[*j][0] != '|' && all->tok[*j] && all->tok
			&& all->tok[*j][0] && piper->args[n][i])
	{
		piper->args[n][i] = ft_calloc(ft_strlen(all->tok[*j]) + 1, 1);
		if (!piper->args[n][i])
			return ;
		piper->args[n][i] = ft_memcpy(piper->args[n][i], all->tok[*j],
				ft_strlen(all->tok[*j]));
		i++;
		*j += 1;
	}
	if (all->tok[*j][0] == '|' && all->tok[*j + 1] && all->tok
			&& all->tok[*j + 1][0])
	*j += 1;
}

static void	first_child(t_piper *piper, t_all *all, int *fd, int n)
{
	int		i;
	int		err;
	pid_t	id;

	i = 0;
	id = fork();
	if (id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		while (all->env_path[i])
		{
			all->cmd = ft_strjoin(all->env_path[i], piper->cmd[n]);
			err = execve(all->cmd, piper->args[n], all->mini_env);
			free(all->cmd);
			i++;
		}
		if (err == -1)
		{
			perror(piper->cmd[n]);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(id, NULL, 0);
	return ;
}

static void	next_children(t_piper *piper, t_all *all, int *fd, int n)
{
	int		i;
	int		err;
	pid_t	id;

	i = 0;
	id = fork();
	if (id == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (id == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		while (all->env_path[i])
		{
			all->cmd = ft_strjoin(all->env_path[i], piper->cmd[n]);
			err = execve(all->cmd, piper->args[n], all->mini_env);
			free(all->cmd);
			i++;
		}
		if (err == -1)
		{
			perror(piper->cmd[n]);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(id, NULL, 0);
	return ;
}

static void	pipe_execution(t_all *all, t_piper *piper)
{
	int			i;
	static int	fd[2];

	i = 0;
	pipe(fd);
	while (i <= all->ops->pipe)
	{
		if (i == 0)
			first_child(piper, all, fd, i);
		else
			next_children(piper, all, fd, i);
		i++;
	}
}

void	piper_initialize(t_all *all, t_piper *piper)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	piper->cmd = ft_calloc((all->ops->pipe + 2), sizeof(*piper->cmd));
	if (!piper->cmd)
		return ;
	piper->args = ft_calloc((all->ops->pipe + 2), sizeof(*piper->args));
	if (!piper->args)
		return ;
	while (i <= all->ops->pipe && all->tok[j] && all->tok && all->tok[j][0])
	{
		piper->cmd[i] = ft_calloc(ft_strlen(all->tok[j]) + 1, 1);
		if (!piper->cmd[i])
			return ;
		piper->cmd[i] = ft_memcpy(piper->cmd[i], all->tok[j],
				ft_strlen(all->tok[j]));
		piper->args[i] = ft_calloc(args_cnt(all->tok, j) + 1,
				sizeof(*piper->args[i]));
		if (!piper->args[i])
			return ;
		args_copy(all, piper, &j, i);
		i++;
	}
}

void	pipex(t_all *all)
{
	t_piper	piper;

	piper_initialize(all, &piper);
	pipe_execution(all, &piper);
	//free_piper(&piper);
}
