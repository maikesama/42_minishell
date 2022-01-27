#include "./../../headers/main.h"

void	executioner(t_all *all)
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
		while (all->env_path[i])
		{
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
	waitpid(0, NULL, 0);	
	return ;
}