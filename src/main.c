/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:49:43 by pceccoli          #+#    #+#             */
/*   Updated: 2021/12/17 16:19:56 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../headers/main.h"

void	ft_exit(t_all *all)
{
	if (all->mini_env)
		free_matrix(all->mini_env);
	if (all->tok)
		free_matrix(all->tok);
	if (all->env_path)
		free_matrix(all->env_path);
	if (all->env_var)
		free_matrix(all->env_var);
	exit(EXIT_SUCCESS);
}

void	initialize_struct(t_all *all)
{
	all->echoflag = 0;
	all->flag1 = 1;
	all->flag2 = 1;
	all->ops->arrow = 0;
	all->ops->worra = 0;
	all->ops->darrow = 0;
	all->ops->dworra = 0;
	all->ops->pipe = 0;
	all->saved_stdout = dup(1);
	all->saved_stdin = dup(0);
}

int	valid_history(t_all *all)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (all->input[i])
	{
		if (all->input[i] == ' ' || all->input[i] == '\t')
			j++;
		i++;
	}
	if (j != i)
		return (1);
	return (0);
}

void	take_input(t_all *all)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if (all->input)
		free(all->input);
	all->input = readline( RL_S"\e[95m"RL_E "MiniShell>>>" RL_S"\e[0m"RL_E );
	if (all->input == NULL)
		ft_exit(all);
	if (valid_history(all))
	{
		add_history(all->input);
		initialize_struct(all);
	}
	else
		return ;
}

int	main(int ac, char **av, char **env)
{
	t_all	all;
	t_ops	ops;

	ft_bzero(&all, sizeof(all));
	ft_bzero(&ops, sizeof(ops));
	free(all.input);
	all.ops = &ops;
	if (ac != 1 || !av || !env)
		return (0);
	get_env(&all, env);
	while (1)
	{
		take_input(&all);
		parser(&all);
		if (all.input)
			free(all.input);
		all.input = NULL;
	}
}
