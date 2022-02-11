/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ut2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:18:35 by mpaci             #+#    #+#             */
/*   Updated: 2021/12/17 16:55:14 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

int	is_spec_char(char c)
{
	int		i;
	char	*specs;

	specs = "<>|";
	i = 0;
	while (specs[i])
	{
		if (c == specs[i])
			return (0);
		i++;
	}
	return (1);
}

void	copy_spc_double(t_all *all, char **tmp, int *i, int *j)
{
	if (all->input[(*i) - 1] != ' ' && all->input[*i - 1])
	{
		tmp[0][*j] = ' ';
		*j += 1;
	}
	tmp[0][*j] = all->input[*i];
	*j += 1;
	tmp[0][*j] = all->input[*i + 1];
	*j += 1;
	if (all->input[*i + 2] != ' ' && all->input[*i + 2])
	{
		tmp[0][*j] = ' ';
		*j += 1;
	}
	*i += 1;
}

void	copy_spc_ut(t_all *all, char **tmp, int *i, int *j)
{
	if (all->input[*i - 1] != ' ' && all->input[*i - 1])
	{
		tmp[0][*j] = ' ';
		*j += 1;
	}
	tmp[0][*j] = all->input[*i];
	*j += 1;
	if (all->input[*i + 1] != ' ' && all->input[*i + 1])
	{
		tmp[0][*j] = ' ';
		*j += 1;
	}
}

void	copy_spc(t_all *all, char *tmp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!all->input)
		return ;
	while (all->input && all->input[i])
	{
		copy_erase(all, &i, tmp, &j);
		if (!is_spec_char(all->input[i]) && all->flag1 == 1 && all->flag2 == 1)
		{
			if (all->input[i + 1] && all->input[i + 1] == all->input[i])
				copy_spc_double(all, &tmp, &i, &j);
			else
				copy_spc_ut(all, &tmp, &i, &j);
			i++;
		}
		if (all->input[i])
			tmp[j++] = all->input[i++];
	}
}

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
	tmp = ft_calloc((ft_strlen(all->input) + len - j), 1);
	ft_memcpy(tmp, all->input, i);
	j = 0;
	n = i;
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
	while (all->input[i] && tmp[n])
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
			i--;
		}
		i++;
	}
}

void	new_input(t_all *all)
{
	char	*check;
	char	*tmp;
	int		j;
	int		i;

	i = 0;
	check = "<>|";
	j = 0;
	while (check[j])
	{
		i += add_spaces(all->input, check[j]);
		j++;
	}
	i -= space_eraser(all, all->input);
	tmp = ft_calloc(ft_strlen(all->input) + i + 1, 1);
	copy_spc(all, tmp);
	all->input = ft_realloc(all->input, ft_strlen(tmp) + 1);
	all->input[ft_strlen(tmp)] = 0;
	j = 0;
	while (tmp[j])
	{
		all->input[j] = tmp[j];
		j++;
	}
	free(tmp);
}
