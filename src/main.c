#include <doom.h>

data_t	data;

void	init_game()
{
	data.posX = 12;
    data.posY = 20;
    data.dirX = -1;
    data.dirY = 0;
    data.planeX = 0;
    data.planeY = 0.66; // FOV is 2 * atan(0.66/1.0)=66° specific to FPS
}

int	main(int ac, char **av)
{
	char	*file;

	if (ac != 2)
	{
		printf("You need to put a .txt map\n");
		exit(0);
	}
	file = av[1];
	init_game();
	// map.map = get_map_line(file);
	init_window(data);	
	return 0;
}
