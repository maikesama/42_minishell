#ifndef PARSER_H
# define PARSER_H
# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"

typedef struct s_redir
{
	int	arrow;
	int	worra;
	int	darrow;
	int	dworra;
}				t_redir;

int	check_special(char *str);
int	spec_chars(char c);
int	check_quotes(const char *input);

#endif