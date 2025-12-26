#include "doom.h"

//parse the map
void	parse_map(char *map)
{
	int		i;
	int		j;
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("You need to put a .txt map\n");
		exit(0);
	}
	parse_map(av[1]);
	raycasting();
	return 0;
}
