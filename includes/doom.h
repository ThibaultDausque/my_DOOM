#ifndef DOOM_H
# define DOOM_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

typedef struct map_s
{
    int     len;
    int     height;
    int     bytes;
    char    dir;
    char    **map;
}   map_t;


// get_map_line
int get_map_line(int fd);


#endif
