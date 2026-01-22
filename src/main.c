#include <doom.h>

# define MAP_ERR "Fatal map error"

static char**	parse_map(char *file)
{
	unsigned int	fd;

	if (!(fd = open(file, O_RDONLY)))
	{
		printf("%s\n", MAP_ERR);
		exit(0);
	}
	get_map_line(fd);
	return NULL;
}

int	main(int ac, char **av)
{
	char	*file;
	// map_t	map;

	if (ac != 2)
	{
		printf("You need to put a .txt map\n");
		exit(0);
	}
	file = av[1];
	parse_map(file);
	// raycasting();
	return 0;
}
