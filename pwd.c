#include "main.h"

void	print_dir(t_all *all)
{
	all->dir = getcwd(all->dir, 0);
	if (all->dir == NULL)
		return ;
	printf("\nDir: %s", all->dir);
}
