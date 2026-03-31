#include <doom.h>

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

void    extract_line(char *line)
{
    int     i = 0;
    int     j = 0;
    char    map[MAP_SIZE][MAP_SIZE];

    while (line[i] && line[i] != '\n')
        i++;
    // substract the line and cat int **map
}

void get_map_line(char *file)
{
    char    line[MAP_SIZE];
    int     fd;
    int     r;
    int     n_bytes = sizeof(line);

    fd = open(file, O_RDONLY);
    if (!fd)
    {
        printf("Error while opening the map.\n");
        exit(0);
    }
    r = read(fd, &line, n_bytes);
    printf("bytes read: %d\n", r);
    // while (r > 0)
    //     r += read(fd, &map, n_bytes);
    line[r] = '\0';
    printf("%s\n", line);
}

void ft_close(int code, data_t *data)
{
	mlx_destroy_window(&data->mlx, &data->mlx_win);
	exit(code);
}
