#include "doom.h"

int	map_size(char *map)
{
	int		i = 0;
	size_t	len = 1;
	int		bytes;
	unsigned int		fd;
	
	if (!(fd = open(map, O_RDONLY)))
	{
		printf("open error\n");
		exit(0);
	}
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, map, len);
		i++;
	}
	return i;
}

int	main(int ac, char **av)
{
	char	*map;

	if (ac != 2)
	{
		printf("You need to put a .txt map\n");
		exit(0);
	}
	map = av[1];
	printf("lines: %d\n", map_size(map));
	// parse_map();
	// raycasting();
	return 0;
}
