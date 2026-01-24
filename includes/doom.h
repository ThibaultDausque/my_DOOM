#ifndef DOOM_H
# define DOOM_H

# define MAP_ERR "Fatal map error"

# define SCREEN_WIDTH 1080
# define SCREEN_HEIGHT 720
# define MAP_SIZE 1024

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <mlx.h>

typedef float   f32;
typedef double  f64;

typedef struct map_s
{
    int     len;
    int     height;
    int     bytes;
    char    dir;
    char    *map;
	void	*mlx;
}   map_t;

typedef struct data_s
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	data_t;

// utils
char* get_map_line(char* file);


// raycasting
int raycasting();

#endif
