#include "./../../headers/main.h"

int	exit_var(t_all *all)
{
	char	*str;
	int		j;

	str = ft_itoa(all->status);
	j = ft_strlen(str);
	free(str);
	return (j);
}

int	check_var_len(t_all *all, int j, int mode)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	all->mode = mode;
	if (mode == 0)
	{
		while (all->mini_env[j][i] && all->mini_env[j][i] != '=')
			i++;
		while (all->mini_env[j][i + len])
			len++;
		return (len);
	}
	else if (mode == 1)
	{
		while (all->env_var[j][i] && all->env_var[j][i] != '=')
			i++;
		while (all->env_var[j][i + len])
			len++;
		return (len);
	}
	return (0);
}

int	variable_found(t_all *all, int i)
{
	int		j;
	int		len;

	j = 0;
	i++;
	while (all->input[i + j] && all->input[i + j] != ' ' && all->input[i + j] != '"' && all->input[i + j] != '\'')
		j++;
	all->str = ft_substr(all->input, i, j);
	if (!ft_strncmp(all->str, "?", ft_strlen(all->str)))
		return (exit_var(all));
	all->pos = 0;
	len = 0;
	while (all->mini_env && all->mini_env[all->pos])
	{
		while (all->mini_env[all->pos][len] && all->mini_env[all->pos][len] != '=')
			len++;
		if (!ft_strncmp(all->str, all->mini_env[all->pos], len))
			return (check_var_len(all, all->pos, 0));
		len = 0;
		all->pos++;
	}
	all->pos = 0;
	while (all->env_var && all->env_var[all->pos])
	{
		while (all->env_var[all->pos][len] && all->env_var[all->pos][len] != '=')
			len++;
		if (!ft_strncmp(all->str, all->env_var[all->pos], len))
			return (check_var_len(all, all->pos, 1));
		len = 0;
		all->pos++;
	}
	free(all->str);
	return (0);
}

void	expand_exit(t_all *all, char *tmp, int *n)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_itoa(all->status);
	while (str[i])
	{
		tmp[*n] = str[i];
		*n += 1;
		i++;
	}
	free(str);
}

void	copy_var(t_all *all, int i, int len)
{
	char	*tmp;
	int		j;
	int		n;

	j = 0;
	n = i + 1;
	while (all->input[n] && all->input[n] != ' ' && all->input[n] != '"' && all->input[n] != '\'')
	{
		n++;
		j++;
	}
	tmp = ft_calloc((ft_strlen(all->input) + len - j) + 1, 1);
	ft_memcpy(tmp, all->input, i);
	n = i;
	i += j + 1;
	j = 0;
	if (!ft_strncmp(all->str, "?", ft_strlen(all->str)))
		expand_exit(all, tmp, &n);
	else if (all->mode == 0)
	{
		while (all->mini_env[all->pos][j] && all->mini_env[all->pos][j] != '=')
			j++;
		j++;
		while (all->mini_env[all->pos][j])
			tmp[n++] = all->mini_env[all->pos][j++];
	}
	else if (all->mode == 1)
	{
		while (all->env_var[all->pos][j] && all->env_var[all->pos][j] != '=')
			j++;
		j++;
		while (all->env_var[all->pos][j] && tmp[n])
			tmp[n++] = all->env_var[all->pos][j++];
	}
	while (all->input[i])
		tmp[n++] = all->input[i++];
	free(all->input);
	all->input = ft_calloc(ft_strlen(tmp) + 1, 1);
	ft_memcpy(all->input, tmp, ft_strlen(tmp));
	free(tmp);
	free(all->str);
}

void	delete_var(t_all *all, int i)
{
	char	*tmp;
	int		j;

	j = 0;
	while(all->input[i + j] && all->input[i + j] != ' ' && all->input[i + j] != '"' && all->input[i + j] != '\'')
		j++;
	tmp = ft_calloc((ft_strlen(all->input) - j) + 1, 1);
	j += i;
	ft_memcpy(tmp, all->input, i);
	while (all->input[j])
		tmp[i++] = all->input[j++];
	free(all->input);
	all->input = ft_calloc(ft_strlen(tmp) + 1, 1);
	ft_memcpy(all->input, tmp, ft_strlen(tmp));
	free(tmp);
}

void	input_expand(t_all *all)
{
	int	i;
	int	len;

	i = 0;
	while (all->input && all->input[i])
	{
		if (all->input[i] == '"' && all->flag2 == 1)
			all->flag1 *= -1;
		if (all->input[i] == '\'' && all->flag1 == 1)
			all->flag2 *= -1;
		if (all->input[i] == '$' && all->flag2 == 1 && (len = variable_found(all, i)))
		{
			copy_var(all, i, len);
			i--;
		}
		else if (all->input[i] == '$' && all->flag2 == 1)
		{
			delete_var(all, i);
			if (!all->input || !all->input[i])
				break ;
			if (i > 0)
				i--;
		}
		i++;
	}
}