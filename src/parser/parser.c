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

void	read_cmd(t_all *all)
{
	int	i;

	i = 0;

	if (!ft_strncmp(all->tok[0], "cd", 2))
		change_directory(all->tok[1], all);
	if (!ft_strncmp(all->tok[0], "pwd", 3))
		print_dir(all);
	if (!ft_strncmp(all->tok[0], "env", 3))
		print_env(all);
	if (!ft_strncmp(all->tok[0], "exit", 5))
		ft_exit(all);
}

int	parser(t_all *all)
{
	int		i;

	i = 0;
	if (!check_quotes(all->input) || !check_special(all->input))
		return (0);
	new_input(all);
	input_tok(all);
	read_cmd(all);
	return (1);
}
