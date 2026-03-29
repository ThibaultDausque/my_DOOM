#include <doom.h>

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

#define PI 3.14159265359f
#define TAU (2.0f * PI)
#define PI_2 (PI / 2.0f)
#define PI_4 (PI / 4.0f)

map_t	map;

void	init_game(data_t *data)
{
	map.posX = 2;
    map.posY = 2;
    map.dirX = -1;
    map.dirY = 0;
    map.planeX = 0;
    map.planeY = 0.66; // FOV is 2 * atan(0.66/1.0)=66° specific to FPS
	init_window(data);
}

int worldMap[5][5] = {
    {1, 1, 1, 1, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 0, 0, 0, 1},
    {1, 1, 1, 1, 1}
};

static void	mlx_put_pxl(data_t *data, int x, int y, int color)
{
	char*	dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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
	int		rgb;
	
	int		drawStart;
	int		drawEnd;

	f64		stepX;
	f64		stepY;

	data->img = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		f64		camX = (2 * x / (double)SCREEN_WIDTH) - 1;
		f64		rayDirX = map.dirX + map.planeX * camX;
		f64		rayDirY = map.dirY + map.planeY * camX;
    	
		mapX = (int)map.posX;
    	mapY = (int)map.posY;
		deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (map.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - map.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (map.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - map.posY) * deltaDistY;
		}

		hit = 0;
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
			
			if (worldMap[mapY][mapX] > 0) hit = 1;
			rgb = RGB_RED;
			// else if (colornb == 2)
			// 	rgb = RGB_GREEN;
			// else if (colornb == 3)
			// 	rgb = RGB_BLUE;
			// else if (colornb == 4)
			// 	rgb = RGB_YELLOW;
		}
		
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		
		if (perpWallDist > 0)
			wall_height = (int)(SCREEN_HEIGHT / perpWallDist);
		
		drawStart = (-wall_height / 2) + (SCREEN_HEIGHT / 2);
		if (drawStart < 0) drawStart = 0;
		
		drawEnd = (wall_height / 2) + (SCREEN_HEIGHT / 2);
		if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

		int		start = drawStart;
		int		end = drawEnd;
		while (start < end) mlx_put_pxl(data, x, start++, rgb);
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img, 0, 0);
	mlx_destroy_image(data->mlx, data->img);
	return 1;
}

int	key_hook(int keycode, map_t *map, keys_t *keys)
{
	f64		oldDirX;
	f64		oldPlaneX;
	f64		v = 0.05; // move speed
	f64		r = 0.05; // rotation speed
	//f64		mapX_max = 3;
	//f64		mapY_max = 3;

	if (keycode == W_KEY) // straight
	{
		if (worldMap[(int)(map->posX + map->dirX*v)][(int)map->posY] == 0)
			map->posX += map->dirX * v;
		
		if (worldMap[(int)(map->posX)][(int)(map->posY + map->dirY*v)] == 0)
			map->posY += map->dirY * v;
	}
	else if (keycode == S_KEY) // back
	{
		if (!worldMap[(int)(map->posX - map->dirX*v)][(int)map->posY])
			map->posX -= map->dirX * v;

		if (!worldMap[(int)map->posX][(int)(map->posY - map->dirY*v)])
			map->posY -= map->dirY * v;
	}
	else if (keycode == D_KEY) // right
	{
		oldDirX = map->dirX;
		map->dirX = map->dirX * cos(-r) - map->dirY * sin(-r);
		map->dirY = oldDirX * sin(-r) + map->dirY * cos(-r);
		oldPlaneX = map->planeX;
		map->planeX = map->planeX * cos(-r) - map->planeY * sin(-r);
		map->planeY = oldPlaneX * sin(-r) + map->planeY * cos(-r);
	}
	else if (keycode == A_KEY) // left
	{
		oldDirX = map->dirX;
		map->dirX = map->dirX * cos(r) - map->dirY * sin(r);
		map->dirY = oldDirX * sin(r) + map->dirY * cos(r);
		oldPlaneX = map->planeX;
		map->planeX = map->planeX * cos(r) - map->planeY * sin(r);
		map->planeY = oldPlaneX * sin(r) + map->planeY * cos(r);
	}

	printf("dir X: %f\n", map->dirX);
	printf("dir Y: %f\n", map->dirY);

	printf("pos X: %f\n", map->posX);
	printf("pos Y: %f\n", map->posY);

	return 0;
}

int	init_window(data_t *data)
{
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Doom");
	#ifdef __APPLE__
		mlx_hook(data->mlx_win, KEY_PRESS, 0, key_hook, &map);
	#else
		mlx_key_hook(data->mlx_win, key_hook, &map);
	#endif
	mlx_hook(data->mlx_win, KEY_PRESS, 0, key_hook, &map);

	mlx_loop_hook(data->mlx, raycasting, data);
	//mlx_hook(data->mlx_win, 2, 1L<<0, ft_close, data);
	mlx_loop(data->mlx);
	return 1;
}