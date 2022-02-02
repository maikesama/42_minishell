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

void	fd_allocation(t_piper *piper, t_all *all)
{
	int	i;

	i = 0;
	piper->fd = malloc((all->ops->pipe + 2) * sizeof(int	*));
	while(i <= all->ops->pipe)
	{
		piper->fd[i] = (int *)malloc(2 * sizeof(int));
		pipe(piper->fd[i]);
		i++;
	}
}

void	pipex(t_all *all)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	t_piper	piper;
	fd_allocation(&piper, all);
	while (all->tok[i] != 0 && all->tok[i][0] != 0)
	{
		piper.cmd = ft_calloc(ft_strlen(all->tok[i]) + 1, 1);
		ft_memcpy(piper.cmd, all->tok[i], ft_strlen(all->tok[i]));
		args_initializer(all, &piper, &i);
		pipe_execution(all, &piper, &cnt);
		free_piper(&piper, all);
		if (!all->tok[i])
			break ;
		if (all->tok[i][0] == '|')
			i += 1;
		cnt++;
	}
	free_fds(piper.fd, all->ops->pipe);
}
