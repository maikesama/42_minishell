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

void	pid_status()
{
	pid_t id;

	id = getpid();
	ft_printf("%d: command not found\n", id);
}

void	read_cmd(t_all *all)
{
	if (all->ops->pipe)
		pipex(all);
	else if (!ft_strncmp(all->tok[0], "$?", ft_strlen(all->tok[0])))
		ft_printf("%d: command not found\n", all->status);
	else if (!ft_strncmp(all->tok[0], "$$", ft_strlen(all->tok[0])))
		pid_status();
	else if (!ft_strncmp(all->tok[0], "export", ft_strlen(all->tok[0])))
		export_var(all);
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
		unset_var(all);
	else if (!ft_strncmp(all->tok[0], "echo", ft_strlen(all->tok[0])))
		echo(all);
	else
		executioner(all);
}

int	parser(t_all *all)
{
	if (!all->input || !all->input[0])
		return (0);
	if (!check_quotes(all->input) || !check_special(all, all->input))
	{
		ft_printf("Error. Wrong input.\n");
		return (0);
	}
	new_input(all);
	input_tok(all);
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
