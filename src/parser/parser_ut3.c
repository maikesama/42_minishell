#include "./../../headers/main.h"

int	space_eraser(char *str)
{
	int flag1;
	int flag2;
	int i;
	int j;

	flag1 = 1;
	flag2 = 1;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '"' && flag2 == 1)
			flag1 *= -1;
		if (str[i] == '\'' && flag1 == 1)
			flag2 *= -1;
		if (str[i] == ' ' && str[i - 1] == ' ' && str[i - 1]
			&& flag1 == 1 && flag2 == 1)
			j++;
		i++;
	}
	return (j);
}

void	copy_erase(t_all *all, int *i, char *tmp, int *j)
{
	if (all->input[*i] == '"' && all->flag1 == 1)
		all->flag2 *= -1;
	if (all->input[*i] == '\'' && all->flag2 == 1)
		all->flag1 *= -1;
	if (all->input[*i] == ' ' && all->input[*i + 1] == ' '
		&& all->flag1 == all->flag2 == 1)
	{
		tmp[*j] = all->input[*i];
		*j += 1;
		while (all->input[*i] == ' ')
			*i += 1;
	}
}