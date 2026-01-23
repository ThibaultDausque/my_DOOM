#include <doom.h>

// int map_dims(int fd)
// {

// }

char* get_map_line(char *file)
{
    unsigned int    fd;
    char            *map;
    int             r;

    map = (char*)malloc((MAP_SIZE + 1) * sizeof(char));
    if (!map)
    {
        printf("%s\n", MAP_ERR);
        exit(0);
    }
    if (!(fd = open(file, O_RDONLY)))
    {
        printf("%s\n", MAP_ERR);
        exit(0);
    }
    r = read(fd, map, sizeof(map));
    if (!r)
    {
        printf("%s\n", MAP_ERR);
        exit(0);
    }
    printf("line:\n%s", map);
    return map;
}