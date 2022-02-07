#include "./../../headers/main.h"

void	check_redirections(t_all *all, int j)
{
	while (all->tok[j] && all->tok[j][0] != '|')
	{
		if (all->tok[j][0] == '>')
		{
			all->ops->arrow++;
			write_on_opt(all, &j);
			j--;
		}
		if (all->tok[j][0] == '<')
		{
			all->ops->worra++;
			input(all, &j);
			j--;
		}
		if (all->tok[j] && all->tok[j][0])
			j++;
	}
}

int	size_matter(t_all *all, int	j)
{
	int	i;

	i = 0;
	while (all->tok[j] && all->tok[j][0] != '|')
	{
		i++;
		j++;
	}
	return (i);
}

void	args_initializer(t_all *all, t_piper *piper, int *i, int cnt)
{
	int	j;

	j = *i;
	check_redirections(all, j);
	piper[cnt].args = ft_calloc(size_matter(all, j) + 1, sizeof(*piper[cnt].args));
	j = 0;
	while (all->tok[*i] && all->tok[*i][0] && all->tok[*i][0] != '|')
	{
		piper[cnt].args[j] = ft_calloc(ft_strlen(all->tok[*i]) + 1, 1);
		ft_memcpy(piper[cnt].args[j], all->tok[*i], ft_strlen(all->tok[*i]));
		*i += 1;
		j++;
	}
}
