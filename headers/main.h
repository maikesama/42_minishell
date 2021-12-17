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
# include "./lib/libft/libft.h"
# include "./lib/ft_printf/ft_printf.h"
# include "./lib/parser.h"

typedef struct s_all
{
	char	*input;
	char	**tok;
	char	*dir;
	t_ops	*ops;
	int		flag1;
	int		flag2;
}				t_all;

int		take_imput(char *str);

int		parser(t_all *all);
void	print_dir(t_all *all);
void	new_input(t_all *all);
void	input_tok(t_all *all);
void	copy_erase(t_all *all, int *i, char *tmp, int *j);

#endif
