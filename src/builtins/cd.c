#include "./../../headers/main.h"

void	change_pwd(t_all *all)
{
	int	i;

	i = 0;
	while (ft_strncmp(all->mini_env[i], "PWD=", 4))
		i++;
	free(all->mini_env[i]);
	all->mini_env[i] = ft_strjoin("PWD=", all->dir);
}

void	change_directory(char	*path, t_all *all)
{
	if (chdir((const char *)path) != 0)
	{
		perror(path);
		return ;
	}
	all->dir = getcwd(all->dir, 0);
	all->dir = getcwd(all->dir, 0);
	change_pwd(all);
	all->dir = NULL;
}