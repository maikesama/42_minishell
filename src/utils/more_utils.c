/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpaci <mpaci@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:51:36 by mpaci             #+#    #+#             */
/*   Updated: 2022/02/09 16:51:37 by mpaci            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

int	check_builtins(t_all *all, t_piper *piper, int cnt)
{
	if (!ft_strncmp(piper[cnt].cmd, "export", ft_strlen(piper[cnt].cmd)))
	{
		export_var(all, piper[cnt].args);
		return (1);
	}
	else if (!ft_strncmp(piper[cnt].cmd, "exit", ft_strlen(piper[cnt].cmd)))
	{
		exit_error(all, piper[cnt].args);
		return (1);
	}
	else if (!ft_strncmp(piper[cnt].cmd, "unset", ft_strlen(piper[cnt].cmd)))
	{
		unset_var(all, piper[cnt].args);
		return (1);
	}
	return (0);
}

void	expand_exit(t_all *all, char *tmp, int *n)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_itoa(all->status);
	while (str[i])
	{
		tmp[*n] = str[i];
		*n += 1;
		i++;
	}
	free(str);
}

int	ft_max(int first, int second)
{
	if (first > second)
		return (first);
	else
		return (second);
}

void	garbage(char **mx, t_all *all, int *len)
{
	while (mx[all->pos][*len]
			&& mx[all->pos][*len] != '=')
		*len += 1;
}
