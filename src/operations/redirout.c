#include "./../../headers/main.h"

void	re_copy_tok(t_all *all, char **tmp)
{
	int	i;

	i = 0;
	all->tok = ft_calloc((line_counter(tmp) + 1), sizeof(*all->tok));
	while (tmp[i])
	{
		all->tok[i] = ft_calloc(ft_strlen(tmp[i]) + 1, 1);
		ft_memcpy(all->tok[i], tmp[i], ft_strlen(tmp[i]));
		i++;
	}
}

void	new_tok(t_all *all, int *i)
{
	char	**tmp;
	int		j;
	int		n;

	j = 0;
	n = 0;
	if (!all->tok[1] || !all->tok[*i + 1])
		return ;
	tmp = ft_calloc(line_counter(all->tok) - 1, sizeof(*tmp));
	while (all->tok[j])
	{
		if (j == *i && all->tok[j + 1])
			j += 2;
		if (all->tok[j] && all->tok[j][0])
		{
			tmp[n] = ft_calloc(ft_strlen(all->tok[j]) + 1, 1);
			ft_memcpy(tmp[n], all->tok[j], ft_strlen(all->tok[j]));
			j++;
			n++;
		}
	}
	free_matrix(all->tok);
	re_copy_tok(all, tmp);
	free_matrix(tmp);
}

void	write_on_opt(t_all *all, int *i)
{
	all->fd_out = -1;
	close(all->fd_out);
	if (all->tok[*i][1] == '>')
		all->fd_out = open(all->tok[*i + 1], O_CREAT | O_APPEND | O_WRONLY, 0777);
	else
		all->fd_out = open(all->tok[*i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if (all->fd_out == -1)
	{
		perror(all->tok[*i + 1]);
		return ;
	}
	new_tok(all, i);
}

void	redirect(t_all *all)
{
	int	i;

	i = 0;
	while (all->tok[i])
	{
		if (all->tok[i][0] == '>')
		{
			if (all->tok[i][1] != 0 && all->tok[i][1] != '>')
				return ;
			write_on_opt(all, &i);
			all->ops->arrow++;
			if (i > 0)
				i--;
		}
		if (all->tok[i][0] == '<')
		{
			if (all->tok[i][1] != 0 && all->tok[i][1] != '<')
				return ;
			input(all, &i);
			all->ops->worra++;
			i--;
		}
		i++;
	}
}

void	set_in_out(t_all *all)
{
	if (all->ops->arrow)
	{
		dup2(all->fd_out, STDOUT_FILENO);
		close(all->fd_out);
	}
	if (all->ops->worra)
	{
		if (all->ops->dworra)
			all->fd_in = open("/tmp/file.txt", O_RDONLY);
		dup2(all->fd_in, STDIN_FILENO);
		close(all->fd_in);
	}
}
