#include <doom.h>

int	main(int ac, char **av)
{
	data_t	data;
	(void) data;
	
	if (ac != 2)
	{
		printf("You need to put a .txt map\n");
		exit(0);
	}
	get_map_line(av[1]);
	// init_game(&data);
	// map.map = get_map_line(file);
	return 0;
}
