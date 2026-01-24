#include <doom.h>

int	main(int ac, char **av)
{
	char	*file;
	map_t	map;

	if (ac != 2)
	{
		printf("You need to put a .txt map\n");
		exit(0);
	}
	file = av[1];
	map.map = get_map_line(file);
	raycasting(&map);
	return 0;
}
