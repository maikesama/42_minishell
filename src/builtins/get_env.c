#include "./../../headers/main.h"

int	line_counter(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}
void	get_path(char *path_line, t_all *all)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_substr(path_line, 5, ft_strlen(path_line) - 5);
	all->env_path = ft_split(tmp, ':');
	while (all->env_path[i])
	{
		all->env_path[i] = ft_strjoin(all->env_path[i], "/");
		i++;
	}
	free (tmp);
}

void	print_env(t_all *all)
{
	int	i;

	i = 0;
	while (all->mini_env[i])
	{
		ft_printf("%s\n", all->mini_env[i]);
		i++;
	}
}

void	get_env(t_all *all, char **env)
{
	int	i;

	i = 0;
	all->mini_env = ft_calloc(line_counter(env) + 1, sizeof(*all->mini_env));
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			get_path(env[i], all);
		all->mini_env[i] = ft_calloc(ft_strlen(env[i]) + 1, 1);
		ft_memcpy(all->mini_env[i], env[i], ft_strlen(env[i]));
		i++;
	}
}