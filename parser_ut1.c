#include "main.h"

int	check_quotes(const char *input)
{
	int	i;
	int	flag1;
	int	flag2;

	i = 0;
	flag1 = 1;
	flag2 = 1;
	while (input[i])
	{
		if (input[i] == '"' && flag2 == 1)
			flag1 *= -1;
		if (input[i] == '\'' && flag1 == 1)
			flag2 *= -1;
		i++;
	}
	if (flag1 == 1 && flag2 == 1)
		return (1);
	return (0);
}

int	spec_chars(char c)
{
	int		j;
	char	*str;

	str = "%%;()&`/\\*[]#˜";
	j = 0;
	while (str[j] && str[j] != c)
	{
		j++;
		if (str[j] == c)
			return (0);
	}
	return (1);
}

int	check_special(char *str)
{
	int		i;
	int		flag1;
	int		flag2;

	i = 0;
	flag1 = 1;
	flag2 = 1;
	while (str[i] && str)
	{
		while (str[i] && str[i] != '"' && str[i] != '\'')
		{
			if (spec_chars(str[i]) == 0 && flag1 == 1 && flag2 == 1)
				return (0);	
			i++;
		}
		if (str[i] == '"')
			flag1 *= -1;
		if (str[i] == '\'')
			flag2 *= -1;
		i++;
	}
	return (1);
}
