#include <doom.h>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

#define PI 3.14159265359f
#define TAU (2.0f * PI)
#define PI_2 (PI / 2.0f)
#define PI_4 (PI / 4.0f)

int worldMap[MAP_WIDTH][MAP_HEIGHT] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

static int	init_window(data_t *data)
{
    void    *mlx;
    void    *mlx_win;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Doom");
    data->img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	mlx_loop(mlx);
    return 1;
}

static void	mlx_put_pxl(data_t *data, int x, int y, int color)
{
	char*	dst;
	
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int raycasting()
{
    f64     posX;
    f64     posY;
    f64     dirX;
    f64     dirY;
    f64     planeX;
    f64     planeY;     // FOV is 2 * atan(0.66/1.0)=66° specific to FPS
    f64     sideDistX;
    f64     sideDistY;
	f64		perpWallDist;

    int     mapX;
    int     mapY;

    f64     deltaDistX;
    f64     deltaDistY;

	// wall hit
	int		hit;
	int		side;
	int		wall_height;

	int		drawStart;
	int		drawEnd;

	data_t	data;

    init_window(&data);
    posX = 22;
    posY = 12;
    dirX = 1;
    dirY = 0;
    planeX = 0;
    planeY = 0.66;
    mapX = (int)posX;
    mapY = (int)posY;

	f64		stepX;
	f64		stepY;

    for (;;)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            f64		camX = 2 * x / (f64)SCREEN_WIDTH - 1;
            f64		rayDirX = dirX + planeX * camX;
            f64		rayDirY = dirY + planeY * camX;
			if (rayDirX != 0) deltaDistX = abs(1 / (int)rayDirX);
			if (rayDirY != 0) deltaDistY = abs(1 / (int)rayDirY);
			
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}

			while (!hit)
			{
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}

				if (worldMap[mapX][mapY] > 0) hit = 1;
			}
			if (!side)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistX);
			wall_height = SCREEN_HEIGHT / (int)perpWallDist;

			drawStart = -wall_height / 2 + SCREEN_HEIGHT / 2;
			if (drawStart < 0) drawStart = 0;

			drawEnd = wall_height / 2 + SCREEN_HEIGHT / 2;
			if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;
			mlx_put_pxl(&data, x, drawEnd - drawStart, 0x00FF0000);
		}
    }
    return 1;
}
