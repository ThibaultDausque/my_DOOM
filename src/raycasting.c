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

static void	mlx_put_pxl(data_t *data, int x, int y, int color)
{
	char*	dst;
	
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// static int	move_cam(data_t *data)
// {

// }

static int raycasting(data_t *data)
{
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
	int		colornb;
	int		rgb;
	
	int		drawStart;
	int		drawEnd;
	
    mapX = (int)data->posX;
    mapY = (int)data->posY;
	hit = 0;

	printf("mapX: %d\n", mapX);

	f64		stepX;
	f64		stepY;

	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		f64		camX = (2 * x) / ((double)SCREEN_WIDTH - 1);
		f64		rayDirX = data->dirX + (data->planeX * camX);
		f64		rayDirY = data->dirY + (data->planeY * camX);
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->posY) * deltaDistY;
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
			
			colornb = worldMap[mapX][mapY];
			if (colornb > 0) hit = 1;
			if (colornb == 1)
				rgb = RGB_RED;
			else if (colornb == 2)
				rgb = RGB_GREEN;
			else if (colornb == 3)
				rgb = RGB_BLUE;
			else if (colornb == 4)
				rgb = RGB_YELLOW;
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

		int		start = drawStart;
		int		end = drawEnd;
		while (start < end)
			mlx_put_pxl(data, x, start++, rgb);
	}
    return 1;
}

int	key_hook(int keycode, data_t data)
{
	f64		oldDirX;
	f64		oldPlaneX;
	f64		v = 0.5; // move speed
	f64		r = 0.5; // rotation speed

	raycasting(&data);
	if (keycode == 119) // straight
	{
		printf("w\n");
		if (worldMap[(int)(data.posX + data.dirX*v)][(int)data.posY] == 0)
			data.posX += data.dirX * v;
		if (worldMap[(int)(data.posX)][(int)(data.posY + data.dirY*v)] == 0)
			data.posY += data.dirY * v;
		printf("posX: %d\n", (int)data.posX);
		printf("posY: %d\n", (int)data.posY);
	}
	else if (keycode == 115) // back
	{
		printf("s\n");
		if (!worldMap[(int)(data.posX - data.dirX*v)][(int)data.posY])
			data.posX -= data.dirX * v;
		if (!worldMap[(int)data.posX][(int)(data.posY - data.dirY*v)])
			data.posX -= data.dirX * v;
	}
	else if (keycode == 100) // right
	{
		printf("d\n");
		oldDirX = data.dirX;
		data.dirX = data.dirX * cos(-r) - data.dirY * sin(-r);
		data.dirY = oldDirX * sin(-r) + data.dirY * cos(-r);
		oldPlaneX = data.planeX;
		data.planeX = data.planeX * cos(-r) - data.planeY * sin(-r);
		data.planeY = oldPlaneX * sin(-r) + data.planeY * cos(-r);
	}
	else if (keycode == 97) // left
	{
		printf("a\n");
		oldDirX = data.dirX;
		data.dirX = data.dirX * cos(r) - data.dirY * sin(r);
		data.dirY = oldDirX * sin(r) + data.dirY * cos(r);
		oldPlaneX = data.planeX;
		data.planeX = data.planeX * cos(r) - data.planeY * sin(r);
		data.planeY = oldPlaneX * sin(-r) + data.planeY * cos(-r);

	}
	return 0;
}

int	init_window(data_t data)
{
	void    *mlx;
	void    *mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Doom");
	data.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	mlx_key_hook(mlx_win, key_hook, &data);
	mlx_put_image_to_window(mlx, mlx_win, data.img, 0, 0);
	mlx_loop(mlx);
	return 1;
}