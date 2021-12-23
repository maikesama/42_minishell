/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 02:49:43 by pceccoli          #+#    #+#             */
/*   Updated: 2021/12/17 16:19:56 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../headers/main.h"

void	initialize_struct(t_all *all)
{
	all->flag1 = 1;
	all->flag2 = 1;
	all->ops->arrow = 0;
	all->ops->worra = 0;
	all->ops->darrow = 0;
	all->ops->dworra = 0;
	all->ops->pipe = 0;
}

void	take_input(t_all *all)
{
	all->input = readline("\e[33m\n>>>\e[0m ");
	if (strlen(all->input) != 0)
	{
		add_history(all->input);
		initialize_struct(all);
	}
	//if (input == ^D || ^C)
	else
		return ;
}

/*char	*command_with_path(const char *str, char **env)
{
	int	i;
	char	*path;
	char	**pathsplit;
	char	**mycmd;

	i = 0;
	while (ft_memcmp(env[i], "PATH=", 5))
		i++;
	path = ft_substr(env[i], 5, ft_strlen(env[i] - 5));
	pathsplit = ft_split(path, ':');
	free(path);
	i = 0;
	while (pathsplit[i])
	{
		ft_strjoin(pathsplit[i], "/");
		i++;
	}

}*/

int	main(int ac, char **av, char **env)
{
	t_all	all;
	t_ops	ops;

	all.ops = &ops;
	if (ac != 1 || !av || !env)
		return (0);
	get_env(&all, env);
	while (1)
	{
		print_dir(&all);
		take_input(&all);
		if (!parser(&all))
			ft_printf("Error.\n");
		//execve("/bin/"input, av, env);
	}
}
