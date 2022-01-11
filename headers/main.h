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
# include <sys/wait.h>
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"
# include "./parser.h"
# include "signal.h"

typedef struct s_piper
{
	char	*cmd;
	char	**args;
	//t_all	*all;
}				t_piper;

typedef struct s_all
{
	int		echoflag;
	char	*input;
	char	**tok;
	char	*dir;
	char	*cmd;
	t_ops	*ops;
	int		flag1;
	int		flag2;
	char	**mini_env;
	char	**env_path;
	char	**env_var;
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
void	executioner(t_all *all);
int		equal_count(t_all *all);
void	save_env_var(t_all *all);
int		check_existence_var(t_all *all);
int		check_existence_env(t_all *all);
void	export_var(t_all *all);
void	re_copy_var(t_all *all, char **tmp);
void	re_copy_env(t_all *all, char **tmp);
void	unset_var(t_all *all);
void	echo(t_all *all);
int		check_special(t_all *all, char *str);
void    pipex(t_all *all);

#endif
