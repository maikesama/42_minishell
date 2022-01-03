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
		i++;
	new_env(all, all->env_var[i]);
	free(str);
}

void	read_cmd(t_all *all)
{
	//int i = 0;
	if (!ft_strncmp(all->tok[0], "cd", 2))
		change_directory(all->tok[1], all);
	else if (!ft_strncmp(all->tok[0], "pwd", 3))
		print_dir(all);
	else if (!ft_strncmp(all->tok[0], "env", 3))
		print_env(all);
	else if (!ft_strncmp(all->tok[0], "exit", 5))
		ft_exit(all);
	else if (equal_count(all))
		save_env_var(all);
	else if (!ft_strncmp(all->tok[0], "export", 6))
		export_var(all);
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
