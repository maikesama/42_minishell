#include "./../../headers/main.h"

void	coming_home(char *path, t_all *all)
{
	int	i;

	i = 0;
	free(path);
	while (all->mini_env[i])
	{
		if (!ft_strncmp("HOME=", all->mini_env[i], 5))
			path = ft_substr(all->mini_env[i], 5, ft_strlen(all->mini_env[i]) - 5);
		i++;
	}
}

void	change_pwd(t_all *all)
{
	int	i;

	i = 0;
	while (i < line_counter(all->mini_env))
	{
		if (!ft_strncmp(all->mini_env[i], "PWD=", 4))
		{
			free(all->mini_env[i]);
			all->mini_env[i] = ft_strjoin("PWD=", all->dir);
		}	
		i++;
	}
}

void	change_directory(t_all *all)
{
	int		i;
	char	*str;

	i = 0;
	if (!all->tok[1] || !ft_strncmp(all->tok[1], "˜", ft_strlen(all->tok[1])))
	{
		str = malloc(1);
		coming_home(str, all);
		if (chdir((const char *)str) != 0)
		{
			perror(str);
			return ;
		}
		free(str);
	}
	else
	{
		if (chdir((const char *)all->tok[1]) != 0)
		{
			perror(all->tok[1]);
			return ;
		}
	}
	all->dir = getcwd(all->dir, 0);
	change_pwd(all);
	free(all->dir);
	all->dir = NULL;
	all->status = 0;
}