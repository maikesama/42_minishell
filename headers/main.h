/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:50:01 by pceccoli          #+#    #+#             */
/*   Updated: 2021/12/17 16:53:49 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "./parser.h"

typedef struct s_all
{
	char	*input;
	char	**tok;
	char	*dir;
	t_ops	*ops;
	int		flag1;
	int		flag2;
	char	**mini_env;
	char	**env_path;
}				t_all;

void	take_input(t_all *all);
int		parser(t_all *all);
void	print_dir(t_all *all);
void	new_input(t_all *all);
void	input_tok(t_all *all);
void	copy_erase(t_all *all, int *i, char *tmp, int *j);
void	get_env(t_all *all, char **env);
void	change_directory(char	*path, t_all *all);
void	print_env(t_all *all);
int		line_counter(char **env);
void	free_matrix(char **mx);
void	ft_exit(t_all *all);

#endif

// #include "./../../headers/main.h"



// void	re_copy(t_all *all, char **tmp)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	all->mini_env = ft_calloc((line_counter(tmp) + 1), sizeof(*all->mini_env));
// 	while (tmp[j])
// 	{
// 		all->mini_env[i] = ft_calloc(ft_strlen(tmp[j]) + 1, 1);
// 		ft_memcpy(all->mini_env[i], tmp[j], ft_strlen(tmp[j]));
// 		i++;
// 		j++;
// 	}
// }

// void	new_env(t_all *all)
// {
// 	int		j;
// 	int		i;
// 	char	**tmp;

// 	j = 0;
// 	i = 0;
// 	tmp = ft_calloc((line_counter(all->mini_env) + 1), sizeof(*tmp));
// 	while (all->mini_env[i])
// 	{
// 		if (!ft_strncmp(all->mini_env[i], "PWD=", 4))
// 		{
// 			tmp[j] = ft_strjoin("PWD=", all->dir);
// 			j++;
// 			i++;
// 		}
// 		tmp[j] = ft_calloc(ft_strlen(all->mini_env[i]) + 1, 1);
// 		ft_memcpy(tmp[j], all->mini_env[i], ft_strlen(all->mini_env[i]));
// 		i++;
// 		j++;
// 	}
// 	free_matrix(all->mini_env);
// 	re_copy(all, tmp);
// 	free_matrix(tmp);
// }

// void	change_directory(char	*path, t_all *all)
// {
// 	if (chdir((const char *)path) != 0)
// 	{
// 		perror("cd :");
// 		return ;
// 	}
// 	all->dir = getcwd(all->dir, 0);
// 	new_env(all);
// 	all->dir = NULL;
// }