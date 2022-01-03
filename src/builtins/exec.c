#include "./../../headers/main.h"

void	executioner(t_all *all)
{
	int		i;
	int		err;
	pid_t	id;

	i = 0;
	id = fork();
	if (id == 0)
	{
		while (all->env_path[i])
		{
			all->cmd = ft_strjoin(all->env_path[i], all->tok[0]);
			err = execve(all->cmd, all->tok, all->mini_env);
			free(all->cmd);
			i++;
		}
		if (err == -1)
			perror(all->tok[0]);
	}
	if (id != 0)
		wait(0);
	return ;
}
