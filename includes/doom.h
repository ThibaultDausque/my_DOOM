#ifndef DOOM_H
# define DOOM_H

# define MAP_ERR "Fatal map error"

# define SCREEN_WIDTH 1080
# define SCREEN_HEIGHT 720
# define MAP_SIZE 1024
# define RGB_RED 0x00FF0000
# define RGB_GREEN 0x0035E400
# define RGB_BLUE 0x000080FF
# define RGB_YELLOW 0x00FFFF00

# define KEY_PRESS 2
# define KEY_RLSE 3


# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>

#ifndef __APPLE__
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
#else
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
#endif

typedef float   f32;
typedef double  f64;

typedef struct map_s
{
    int     len;
    int     height;
    int     bytes;
    char    dir;
    char    *map;
	f64		posX;
	f64		dirX;
	f64		posY;
	f64		dirY;
	f64		planeX;
	f64		planeY;
}   map_t;

typedef struct data_s
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*mlx_win;
}	data_t;

// utils
char*	get_map_line(char* file);
int		ft_close(int keycode, data_t *data);

// raycasting
int		init_window(data_t *data);
void	init_game(data_t *data);

#endif
