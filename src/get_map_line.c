#include <doom.h>

int get_map_line(int fd)
{
    char            *buff = NULL;
    // static char     **map;
    int             r;

    r = 1;
    while (r > -1)
    {
        r = read(fd, buff, 10);
        if (r < 1)
            break ;
        buff[r] = '\0';
    }
    printf("line: %s", buff);
    return 1;
}