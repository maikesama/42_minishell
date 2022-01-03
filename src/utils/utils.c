#include "./../../headers/main.h"

void	free_matrix(char **mx)
{
	int	i;

	i = 0;
	while (mx[i])
	{
		free(mx[i]);
		i++;
	}
	free(mx);
}

int	check_existence_env(t_all *all)
{
	char    *str;
	int     i;

	i = 0;
	if (!all->mini_env)
		return (-1);
	while (all->tok[0][i] != '=')
		i++;
	str = ft_calloc(i + 1, 1);
	ft_memcpy(str, all->tok[0], i);
	i = 0;
	while (all->mini_env[i])
	{
		if (!ft_strncmp(str, all->mini_env[i], ft_strlen(str)))
			return (i);
		i++;
	}
	free(str);
	return (-1);
}

int	check_existence_var(t_all *all)
{
	char    *str;
	int     i;

	i = 0;
	if (!all->env_var)
		return (-1);
	while (all->tok[0][i] != '=')
		i++;
	str = ft_calloc(i + 1, 1);
	ft_memcpy(str, all->tok[0], i);
	i = 0;
	while (all->env_var[i])
	{
		if (!ft_strncmp(str, all->env_var[i], ft_strlen(str)))
			return (i);
		i++;
	}
	free(str);
	return (-1);
}
