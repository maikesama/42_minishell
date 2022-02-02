#include "./../../headers/main.h"

void	child_red(t_all *all, int *i)
{
	char	*input;
	int		fd;

	fd = -1;
	close(fd);
	fd = open("/tmp/file.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror("fd");
		return ;
	}
	if (!all->tok[*i + 1])
		exit(EXIT_SUCCESS);
	while (ft_strncmp(input, all->tok[*i + 1], ft_strlen(all->tok[*i + 1])))
	{
		input = readline("\e[95m>\e[0m ");
		if (!ft_strncmp(input, all->tok[*i + 1], ft_strlen(all->tok[*i + 1])))
		{
			free(input);
			close(fd);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(input, fd);
		ft_putchar_fd('\n', fd);
		free(input);
	}
}


void	dworra(t_all *all, int *i)
{
	pid_t	red;

	all->fd_in = -1;
	close(all->fd_in);
	all->ops->dworra++;

	red = fork();
	if (red == -1)
		return ;
	else if (red == 0)
		child_red(all, i);
	else
	{
		waitpid(0, NULL, 0);
		new_tok(all, i);
	}
}

void	input(t_all *all, int *i)
{
	all->fd_in = -1;
	close(all->fd_in);
	if (all->tok[*i][1] == '<')
	{
		dworra(all, i);
		return ;
	}
	all->fd_in = open(all->tok[*i + 1], O_RDONLY, 0777);
	if (all->fd_in == -1)
	{
		perror(all->tok[*i + 1]);
		return ;
	}
	new_tok(all, i);
}

void	reset_in_out(t_all *all)
{
	if (all->ops->arrow)
	{
		dup2(all->saved_stdout, 1);
		close(all->saved_stdout);
	}
	if (all->ops->worra)
	{
		dup2(all->saved_stdin, 0);
		close(all->saved_stdin);
	}
}
