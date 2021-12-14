/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pceccoli <pceccoli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:00:00 by pceccoli          #+#    #+#             */
/*   Updated: 2021/12/13 18:10:00 by pceccoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	parser(t_all *all)
{
	int		i;

	i = 0;
	if (!check_quotes(all->input) || !check_special(all->input))
		return (0);
	return (1);
}