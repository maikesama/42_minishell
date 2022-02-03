#include "./../../headers/main.h"

void	echo_var(t_all *all, int *i, int *j)
{
	char	*str;
	int		l;

	l = 0;
	*j += 1;
	while (all->tok[*i][*j + l] && all->tok[*i][*j + l] != '\''
		&& all->tok[*i][*j + l] != '"')
		l++;
	str = ft_calloc(l + 1, 1);
	l = 0;
	while (all->tok[*i][*j + l] && all->tok[*i][*j + l] != '\''
		&& all->tok[*i][*j + l] != '"')
	{
		str[l] = all->tok[*i][*j + l];
		l++;
	}
	*j += l;
	if (all->tok[*i][*j] == '"')
		*j += 1;
	if (is_var(all, str))
		write_var(all, str);
	free(str);
}

void    echo_just_for_norm(t_all *all, int i, int *j)
{
	while (all->tok[i][*j])
	{
		if (all->tok[i][*j] == '"' && all->flag1 == 1)
		{
			all->flag2 *= -1;
			*j += 1;
		}
		else if (all->tok[i][*j] == '\'' && all->flag2 == 1)
		{
			all->flag1 *= -1;
			*j += 1;
		}
		if (all->tok[i][*j] == '$' && all->flag1 == 1)
			echo_var(all, &i, &*j);
		if (all->tok[i][*j])
		{
			write(1, &all->tok[i][*j], 1);
			*j += 1;
		}
	}
}

void	skip_flags(t_all *all, int *i)
{
	int	f;
	int	j;

	f = 0;
	j = 2;
	while (!ft_strncmp(all->tok[*i], "-n", 2))
	{
		while (all->tok[*i][j])
		{
			if (all->tok[*i][j] != 'n')
			{
				f = 1;
				break ;
			}
			j++;
		}
		if (f == 1)
			break ;
		j = 2;
		all->echoflag = 1;
		*i += 1;
	}
}

void	echo(t_all *all)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!all->tok[1])
	{
		write(1, "\n", 1);
		return ;
	}
	skip_flags(all, &i);
	while (all->tok[i])
	{
		echo_just_for_norm(all, i, &j);
		j = 0;
		i++;
	}
	if (all->echoflag == 0)
		ft_printf("\n");
	else if (all->echoflag == 1)
		all->echoflag = 0;
	all->status = 0;
}
