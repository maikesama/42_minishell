/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:45:56 by pceccoli          #+#    #+#             */
/*   Updated: 2022/02/04 19:45:58 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../../headers/main.h"

void	print_dir(t_all *all)
{
	all->dir = getcwd(all->dir, 0);
	if (all->dir == NULL)
		return ;
	ft_printf("%s", all->dir);
	all->dir = NULL;
	all->status = 0;
}
