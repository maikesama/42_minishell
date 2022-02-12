/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:28:48 by mpaci             #+#    #+#             */
/*   Updated: 2021/12/17 16:34:32 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <stdlib.h>
# include <unistd.h>
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

typedef struct s_ops
{
	int	arrow;
	int	worra;
	int	darrow;
	int	dworra;
	int	pipe;
}				t_ops;

int		spec_chars(char c);
int		check_quotes(const char *input);
void	jeyer(char	*str, int i, int *j, char spec_char);
int		add_spaces(char *str, char spec_char);

#endif