#include "main.h"

void	print_dir(t_all *all)
{
	all->dir = getcwd(all->dir, 0);
	if (all->dir == NULL)
		return ;
	ft_printf("\nDir: %s", all->dir);
	all->dir = NULL;
}
