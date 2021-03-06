/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:50:01 by pceccoli          #+#    #+#             */
/*   Updated: 2022/02/07 11:52:51 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define RL_S "\1"
# define RL_E "\2"

# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include "./parser.h"
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"

typedef struct s_piper
{
	char	*cmd;
	char	**args;
}				t_piper;

typedef struct s_all
{
	char	*str;
	int		redirected;
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
	int		fd_out;
	int		fd_in;
	int		saved_stdout;
	int		saved_stdin;
	int		status;
	int		mode;
	int		pos;
	int		**fd;
}				t_all;

void	take_input(t_all *all);
int		space_eraser(t_all *all, char *str);
int		parser(t_all *all);
void	print_dir(t_all *all);
void	new_input(t_all *all);
void	input_tok(t_all *all);
void	copy_erase(t_all *all, int *i, char *tmp, int *j);
void	get_env(t_all *all, char **env);
void	change_directory(t_all *all);
void	cd_error(char *str);
void	print_env(t_all *all);
int		line_counter(char **env);
void	free_matrix(char **mx);
void	ft_exit(t_all *all);
void	executioner(t_all *all);
int		equal_count(t_all *all, int line);
void	save_env_var(t_all *all);
int		check_existence_var(t_all *all);
int		check_existence_env(t_all *all);
void	re_copy_var(t_all *all, char **tmp);
void	re_copy_env(t_all *all, char **tmp);
void	unset_var(t_all *all, char **mx);
void	echo(t_all *all);
int		check_special(char *str);
void	pipex(t_all *all);
void	set_in_out(t_all *all);
void	reset_in_out(t_all *all);
void	redirect(t_all *all);
void	new_tok(t_all *all, int *i);
void	re_copy_tok(t_all *all, char **tmp);
int		input(t_all *all, int *i);
void	write_on_opt(t_all *all, int *i);
void	rl_replace_line(const char *text, int clear_undo);
void	sig_handler(int signo);
void	new_tok_pipe(t_all *all, int *i);
void	pipe_execution(t_all *all, t_piper *piper);
void	args_initializer(t_all *all, t_piper *piper, int *i, int cnt);
int		is_var(t_all *all, char *str);
void	write_var(t_all *all, char *str);
void	ft_wait(t_all *all, pid_t id);
void	get_path(char *path_line, t_all *all);
void	ft_wait_pipe(t_all *all, pid_t *id);
void	export_var(t_all *all, char **mx);
int		exit_error(t_all *all, char **mx);
void	ut_stup_two(char *str, t_all *all, int *i, int *j);
void	take_path(t_all *all);
void	child_launcher(t_piper *piper, t_all *all, int cnt);
void	err_pipe_exec(t_piper *piper, int cnt);
void	input_expand(t_all *all);
void	real_tok(t_all *all);
int		check_builtins(t_all *all, t_piper *piper, int cnt);
int		input_expand_ut(t_all *all, int *i, int len);
void	expand_exit(t_all *all, char *tmp, int *n);
void	delete_var(t_all *all, int i);
int		ft_max(int first, int second);
void	garbage(char **mx, t_all *all, int *len);

#endif
