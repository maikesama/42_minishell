/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:52:15 by mpaci             #+#    #+#             */
/*   Updated: 2022/02/09 16:52:16 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	put_child_red(char *input, int fd)
{
	ft_putstr_fd(input, fd);
	ft_putchar_fd('\n', fd);
}

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
		put_child_red(input, fd);
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

int	input(t_all *all, int *i)
{
	all->fd_in = -1;
	close(all->fd_in);
	if (all->tok[*i][1] == '<')
	{
		dworra(all, i);
		return (1);
	}
	all->fd_in = open(all->tok[*i + 1], O_RDONLY, 0777);
	if (all->fd_in == -1)
	{
		perror(all->tok[*i + 1]);
		return (0);
	}
	new_tok(all, i);
	return (1);
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
