#include <doom.h>

// int map_dims(int fd)
// {

// }

void    init_keys(keys_t* keys)
{
    keys->w = 0;
    keys->a = 0;
    keys->s = 0;
    keys->d = 0;
}

int key_press(int keycode, keys_t* keys)
{
    if (keycode == W_KEY) keys->w = 1;
    if (keycode == A_KEY) keys->a = 1;
    if (keycode == S_KEY) keys->s = 1;
    if (keycode == D_KEY) keys->d = 1;
    return keycode;
}

int key_rlse(int keycode, keys_t* keys)
{
    if (keycode == W_KEY) keys->w = 0;
    if (keycode == A_KEY) keys->a = 0;
    if (keycode == S_KEY) keys->s = 0;
    if (keycode == D_KEY) keys->d = 0;
    return keycode;
}

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
    r = read(fd, map, MAP_SIZE);
    if (!r)
    {
        printf("%s\n", MAP_ERR);
        exit(0);
    }
    printf("line:\n%s", map);
    return map;
}

void ft_close(int code, data_t *data)
{
	mlx_destroy_window(&data->mlx, &data->mlx_win);
	exit(code);
}
