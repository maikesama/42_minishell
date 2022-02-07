#include "./../../headers/main.h"

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

void	free_fds(int **fd, int lim)
{
	int	i;

	i = 0;
	while(i <= lim)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	fd_allocation(t_all *all)
{
	int	i;

	i = 0;
	all->fd = malloc((all->ops->pipe + 2) * sizeof(int	*));
	while(i <= all->ops->pipe)
	{
		all->fd[i] = (int *)malloc(2 * sizeof(int));
		pipe(all->fd[i]);
		i++;
	}
}

void	pipex(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	t_piper	*piper;

	piper = malloc((all->ops->pipe + 2) * sizeof(*piper));
	fd_allocation(all);
	while (all->tok[i] != 0 && all->tok[i][0] != 0 && j <= all->ops->pipe)
	{
		piper[j].cmd = ft_calloc(ft_strlen(all->tok[i]) + 1, 1);
		ft_memcpy(piper[j].cmd, all->tok[i], ft_strlen(all->tok[i]));
		args_initializer(all, piper, &i, j);
		if (!all->tok[i])
			break ;
		if (all->tok[i][0] == '|')
			i += 1;
		j++;
	}
	pipe_execution(all, piper);
	free_fds(all->fd, all->ops->pipe);
}
