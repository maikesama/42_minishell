#include "./../../headers/main.h"

//when variable dont exist and ""

int	is_var(t_all *all, char *str)
{
	int	i;

	i = 0;
	if (!all->env_var || !all->env_var[0])
		return (0);
	while (all->env_var[i])
	{
		if (!ft_strncmp(str, all->env_var[i], ft_strlen(str)))
			return (1);
		i++;
	}
	return (0);
}

void	write_var(t_all *all, char *str)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (all->env_var[i])
	{
		while (all->env_var[i][l] != '=')
			l++;
		if (!ft_strncmp(str, all->env_var[i], l))
		{
			l++;
			while (all->env_var[i][l])
			{
				write(1, &all->env_var[i][l], 1);
				l++;
			}
		}
		l = 0;
		i++;
	}
}

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
		else if (all->tok[i][*j] == '$' && all->flag1 == 1)
			echo_var(all, &i, &*j);
		if (all->tok[i][*j])
		{
			write(1, &all->tok[i][*j], 1);
			*j += 1;
		}
	}
}

void	echo(t_all *all)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!ft_strncmp(all->tok[i], "-n", ft_strlen(all->tok[i])))
	{
		all->echoflag = 1;
		i++;
	}
	while (all->tok[i])
	{
		echo_just_for_norm(all, i, &j);
		j = 0;
		i++;
	}
}
