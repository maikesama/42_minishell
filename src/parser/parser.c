/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:00:00 by pceccoli          #+#    #+#             */
/*   Updated: 2021/12/17 16:38:56 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	echo_one(t_all *all, int *i, int *j)
{
	*j += 1;
	while (all->tok[*i][*j] && all->tok[*i][*j] != '\'')
	{
		write(1, &all->tok[*i][*j], 1);
		*j += 1;
	}
	*j += 1;
}

int	is_var(t_all *all, char *str)
{
	int	i;

	i = 0;
	if (!all->env_var)
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
	if (is_var(all, str))
		write_var(all, str);
	free(str);
}

void	echo(t_all *all)
{
	//control flag -n
	//control env var
	//control ""
	//segmentation fault with long arguments
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (all->tok[i])
	{
		while (all->tok[i][j])
		{
			if (all->tok[i][j] == '\'')
				echo_one(all, &i, &j);
			if (all->tok[i][j] == '$')
				echo_var(all, &i, &j);
			if (all->tok[i][j] == '\'')
				echo_one(all, &i, &j);
			if (all->tok[i][j])
			{
				write(1, &all->tok[i][j], 1);
				j++;
			}
		}
		j = 0;
		i++;
	}
}

void	read_cmd(t_all *all)
{
	//int i = 0;
	if (equal_count(all))
		save_env_var(all);
	else if (!ft_strncmp(all->tok[0], "cd", ft_strlen(all->tok[0])))
		change_directory(all->tok[1], all);
	else if (!ft_strncmp(all->tok[0], "pwd", ft_strlen(all->tok[0])))
		print_dir(all);
	else if (!ft_strncmp(all->tok[0], "env", ft_strlen(all->tok[0])))
		print_env(all);
	else if (!ft_strncmp(all->tok[0], "exit", ft_strlen(all->tok[0])))
		ft_exit(all);
	else if (equal_count(all))
		save_env_var(all);
	else if (!ft_strncmp(all->tok[0], "export", ft_strlen(all->tok[0])))
		export_var(all);
	else if (!ft_strncmp(all->tok[0], "unset", ft_strlen(all->tok[0])))
		unset_var(all);
	else if (!ft_strncmp(all->tok[0], "echo", ft_strlen(all->tok[0])))
		echo(all);
	else
		executioner(all);
}

int	parser(t_all *all)
{
	int		i;

	i = 0;
	if (!all->input || !all->input[0])
		return (0);
	if (!check_quotes(all->input) || !check_special(all->input))
	{
		ft_printf("Error. Wrong input.\n");
		return (0);
	}
	new_input(all);
	input_tok(all);
	read_cmd(all);
	return (1);
}
