#include "./../../headers/main.h"

int	equal_count(t_all *all, int line)
{
	int	i;


	i = 0;
	while (all->tok[line][i])
	{
		if (all->tok[line][i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	re_copy_var(t_all *all, char **tmp)
{
	int	i;

	i = 0;
	all->env_var = ft_calloc((line_counter(tmp) + 1), sizeof(*all->env_var));
	while (tmp[i])
	{
		all->env_var[i] = ft_calloc(ft_strlen(tmp[i]) + 1, 1);
		ft_memcpy(all->env_var[i], tmp[i], ft_strlen(tmp[i]));
		i++;
	}
}

int	change_var(t_all *all)
{
	int		i;
	int		j;
	char	*new;
	
	i = check_existence_env(all);
	j = check_existence_var(all);
	if (j == -1)
		return (0);
	new = ft_strjoin(all->tok[0], "");
	free(all->env_var[j]);
	all->env_var[j] = ft_strjoin(new, "");
	ft_printf("%d\n", i);
	if (i != -1)
	{
		free(all->mini_env[i]);
		all->mini_env[i] = ft_strjoin(new, "");
	}
	free(new);
	return (1);
}

void	save_env_var(t_all *all)
{
	char	**tmp;
	int		i;
	
	i = 0;
	if (line_counter(all->tok) != 1)
		return ;
	if (change_var(all))
		return ;
	tmp = ft_calloc(line_counter(all->env_var) + 2, sizeof(*tmp));
	if (all->env_var)
	{
		while (all->env_var[i])
		{
			tmp[i] = ft_calloc(ft_strlen(all->env_var[i]) + 1, 1);
			ft_memcpy(tmp[i], all->env_var[i], ft_strlen(all->env_var[i]));
			i++;
		}
	}
	tmp[i] = ft_calloc(ft_strlen(all->tok[0]) + 1, 1);
	ft_memcpy(tmp[i], all->tok[0], ft_strlen(all->tok[0]));
	if (all->env_var)
		free_matrix(all->env_var);
	re_copy_var(all, tmp);
	free_matrix(tmp);
}
