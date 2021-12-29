#include "./../../headers/main.h"

void	free_matrix(char **mx)
{
	int	i;

	i = 0;
	while (mx[i])
	{
		free(mx[i]);
		i++;
	}
	free(mx);
}
