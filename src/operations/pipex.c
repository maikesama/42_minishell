#include "./../../headers/main.h"

int	args_cnt(char **tok, int n)
{
	int	i;

	i = 0;
	while (tok[n][0] != '|')
	{
		n++;
		i++;
	}
	return (i);
}

void	free_piper(t_piper *piper, t_all *all)
{
	int	i;

	i = 0;
	while (i <= all->ops->pipe)
	{
		if (piper[i].cmd && piper[i].cmd[0])
			free(piper[i].cmd);
		if (piper[i].args && piper[i].args[0])
			free_matrix(piper[i].args);
		i++;
	}
	free(piper);
}

void	args_copy(t_all *all, t_piper *piper, int *j, int n)
{
	int	i;

	i = 0;
	while (all->tok[*j][0] != '|' && all->tok[*j] && all->tok
			&& all->tok[*j][0])
	{
		piper[n].args[i] = ft_calloc(ft_strlen(all->tok[*j]) + 1, 1);
		if (!piper[n].args[i])
		{
			//free_piper(all);
			return ;
		}
		piper[n].args[i] = ft_memcpy(piper[n].args[i], all->tok[*j]
											, ft_strlen(all->tok[*j]));
		ft_printf("%s\n", piper[n].args[i]);
		if (!piper[n].args[i])
		{
			//free_piper(all);
			return ;
		}
		i++;
		*j += 1;
	}
	// if (all->tok[*j][0] == '|' && all->tok[*j] && all->tok
	// 		&& all->tok[*j][0])
	// 	*j += 1;
}

void	piper_initialize(t_all *all, t_piper *piper)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= all->ops->pipe && piper)
	{
		piper[i].cmd = ft_calloc(ft_strlen(all->tok[j]) + 1, 1);
		if (!piper[i].cmd)
		{
			//free_piper(all);
			return ;
		}
		piper[i].cmd = ft_memcpy(piper[i].cmd, all->tok[j]
								, ft_strlen(all->tok[j]));
		piper[i].args = ft_calloc(args_cnt(all->tok, j) + 1
								, sizeof(*piper[i].args));
		if (!piper[i].args)
		{
			//free_piper(all);
			return ;
		}
		args_copy(all, piper, &j, i);
		printf ("%d\n", i);
		i++;
	}
}

void    pipex(t_all *all)
{
	// int	child1;
	// int	child2;
	// int	fd[2];
	int		i;
	int		j;
	t_piper	*piper;

	j = 0;
	i = 0;
	piper = malloc((all->ops->pipe + 1) * sizeof(*piper));
	if (!piper)
		return ;
	piper_initialize(all, piper);
	//free_piper(piper, all);
}