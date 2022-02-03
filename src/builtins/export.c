#include "./../../headers/main.h"

void	re_copy_env(t_all *all, char **tmp)
{
	int	i;

	i = 0;
	all->mini_env = ft_calloc((line_counter(tmp) + 1), sizeof(*all->mini_env));
	while (tmp[i])
	{
		all->mini_env[i] = ft_calloc(ft_strlen(tmp[i]) + 1, 1);
		ft_memcpy(all->mini_env[i], tmp[i], ft_strlen(tmp[i]));
		i++;
	}
}

void	new_env(t_all *all, char *env_var)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_calloc((line_counter(all->mini_env) + 2), sizeof(*tmp));
	while (all->mini_env[i])
	{
		tmp[i] = ft_calloc(ft_strlen(all->mini_env[i]) + 1, 1);
		ft_memcpy(tmp[i], all->mini_env[i], ft_strlen(all->mini_env[i]));
		i++;
	}
	tmp[i] = ft_strjoin(env_var, "");
	free_matrix(all->mini_env);
	re_copy_env(all, tmp);
	free_matrix(tmp);
}

void	export_var(t_all *all)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	if (!all->tok[1])
		return ;
	while (all->tok[1][i] != '=')
		i++;
	str = ft_calloc(i + 1, 1);
	ft_memcpy(str, all->tok[1], i);
	i = 0;
	while (ft_strncmp(str, all->env_var[i], ft_strlen(str)))
	{
		if (ft_strncmp(str, all->env_var[i], ft_strlen(str)))
			j = 0;
		else
			j = 1;
		i++;
	}
	if (j == 0)
		return ;
	new_env(all, all->env_var[i]);
	free(str);
	all->status = 0;
}