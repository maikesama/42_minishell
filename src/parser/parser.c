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

// void	pid_status(void)
// {
// 	pid_t	id;

// 	id = getpid();
// 	ft_printf("%d: command not found\n", id);
// }

void	read_cmd(t_all *all)
{
	if (all->tok[0][0] == 0)
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

int	real_size(t_all *all, int i)
{
	int	j;
	int	cnt;

	cnt = 0;
	j = 0;
	while (all->tok[i][j])
	{
		if (all->tok[i][j] == '"' && all->flag2 == 1)
		{
			cnt++;
			all->flag1 *= -1;
		}
		else if (all->tok[i][j] == '\'' && all->flag1 == 1)
		{
			cnt++;
			all->flag2 *= -1;
		}
		j++;
	}
	return (cnt);
}

void	real_copy(t_all *all, char **tmp, int i)
{
	int	j;
	int	n;

	j = 0;
	n = 0;
	while (all->tok[i][j])
	{
		if (all->tok[i][j] == '"' && all->flag2 == 1)
		{
			j++;
			all->flag1 *= -1;
		}
		else if (all->tok[i][j] == '\'' && all->flag1 == 1)
		{
			j++;
			all->flag2 *= -1;
		}
		else
			tmp[i][n++] = all->tok[i][j++];
	}
}

void	real_tok(t_all *all)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(line_counter(all->tok) + 1, sizeof(*tmp));
	if (!tmp)
		return ;
	while (all->tok[i])
	{
		tmp[i] = ft_calloc((ft_strlen(all->tok[i]) - real_size(all, i)) + 1, 1);
		real_copy(all, tmp, i);
		i++;
	}
	free_matrix(all->tok);
	re_copy_tok(all, tmp);
	free_matrix(tmp);
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

int	parser(t_all *all)
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
