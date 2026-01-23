#include <doom.h>

int raycasting()
{
    void    *mlx;
    void    *mlx_win;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Doom");
    mlx_loop(mlx);
    return 1;
}