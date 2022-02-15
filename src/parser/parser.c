/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:00:00 by pceccoli          #+#    #+#             */
/*   Updated: 2022/02/07 11:55:04 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	read_cmd(t_all *all)
{
	if (all->tok && all->tok[0] && all->tok[0][0] == 0)
		ft_printf(" : command not found\n");
	else if (all->ops->pipe > 0)
		pipex(all);
	else if (!ft_strncmp(all->tok[0], "export", ft_strlen(all->tok[0])))
		export_var(all, all->tok);
	else if (equal_count(all, 0))
		save_env_var(all);
	else if (!ft_strncmp(all->tok[0], "cd", ft_strlen(all->tok[0])))
		change_directory(all);
	else if (!ft_strncmp(all->tok[0], "pwd", ft_strlen(all->tok[0])))
		print_dir(all);
	else if (!ft_strncmp(all->tok[0], "env", ft_strlen(all->tok[0])))
		print_env(all);
	else if (!ft_strncmp(all->tok[0], "exit", ft_strlen(all->tok[0])))
		ft_exit(all);
	else if (!ft_strncmp(all->tok[0], "unset", ft_strlen(all->tok[0])))
		unset_var(all, all->tok);
	else if (!ft_strncmp(all->tok[0], "echo", ft_strlen(all->tok[0])))
		echo(all);
	else
		executioner(all);
}

void	check_for_pipex(t_all *all)
{
	int	i;

	i = 0;
	all->ops->pipe = 0;
	while (all->tok && all->tok[i])
	{
		if (all->tok[i][0] && all->tok[i][0] == '|')
			all->ops->pipe++;
		i++;
	}
}

int	check_space(char *str)
{
	char	*tmp;

	tmp = ft_calloc(ft_strlen(str) + 1, 1);
	ft_memset(tmp, ' ', ft_strlen(str));
	if (!ft_strncmp(tmp, str, ft_strlen(str)))
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

int	check_all(t_all *all)
{
	if (!all->input || !all->input[0] || !check_space(all->input))
	{
		if (all->env_path)
			free_matrix(all->env_path);
		return (0);
	}
	if (!check_quotes(all->input) || !check_special(all->input))
	{
		ft_printf("Error. Wrong input.\n");
		return (0);
	}
	return (1);
}

int	parser(t_all *all)
{
	if (!check_all(all))
		return (0);
	new_input(all);
	input_expand(all);
	input_tok(all);
	real_tok(all);
	check_for_pipex(all);
	if (!all->ops->pipe)
	{
		redirect(all);
		set_in_out(all);
	}
	read_cmd(all);
	if (all->tok && all->tok[0])
		free_matrix(all->tok);
	reset_in_out(all);
	if (all->env_path && all->env_path[0])
		free_matrix(all->env_path);
	return (1);
}
