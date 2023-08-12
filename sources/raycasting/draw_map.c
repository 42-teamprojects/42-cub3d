/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:18:23 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/12 10:32:59 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_rgba(int r, int g, int b, float a)
{
    int color;

    color = r << 24 | g << 16 | b << 8 | (int)a * 255;
    return (color);
}

void rect(float x, float y, int width, int height, int color)
{
	int i;
	int j;
	i = x;
	while (i < x + width)
	{
		j = 0;
		while (height > y && HEIGHT > y)
		{
			mlx_put_pixel(g_game->img_map, x, y, color);
			y++;
		}
		i++;
	}
}
void	draw_pixels(mlx_image_t **img, float h, float w, int color)
{
	float	i;
	float	j;

	i = h;
	while (i < h + TILE_SIZE)
	{
		j = w;
		while (j < w + TILE_SIZE)
		{
			mlx_put_pixel(*img, i, j, color);
			j++;
		}
		i++;
	}
}

void	draw_grid()
{
	float	x;
	float	y;
	
	x = 0;
	while (x < g_game->map->width * TILE_SIZE)
	{
		y = 0;
		while (y < g_game->map->height * TILE_SIZE)
		{
			mlx_put_pixel(g_game->img_map, x, y, get_rgba(5, 15, 255, 1));
			y++;
		}
		x += TILE_SIZE;
	}
	y = 0;
	while (y < g_game->map->height * TILE_SIZE)
	{
		x = 0;
		while (x < g_game->map->width * TILE_SIZE)
		{
			mlx_put_pixel(g_game->img_map, x, y, get_rgba(5, 15, 255, 1));
			x++;
		}
		y += TILE_SIZE;
	}
}


void	draw_player(mlx_image_t **img, float posx, float posy, int color)
{
	float	i;
	float	j;

	i = posx - 3;
	while (i < (posx +  (TILE_SIZE / 5)) - 3 )
	{
		j = posy - 3;
		while (j < posy +  (TILE_SIZE / 5) - 3 )
		{
			mlx_put_pixel(*img, i, j, color);
			j++;
		}
		i++;
	}

}

void	draw_map()
{

	int	i;
	int	j;
	
	i = 0;
	while(i < g_game->map->width * TILE_SIZE)
	{
		j = 0;
		while(j < g_game->map->height * TILE_SIZE)
		{
			mlx_put_pixel(g_game->img_map, i, j, 0x00000000);
			j++;
		}
		i++;
	} 
	i = 0;
	while (g_game->map->map[i])
	{
		j = 0;
		while (g_game->map->map[i][j])
		{
			if (g_game->map->map[i][j] == '1')
				draw_pixels(&g_game->img_map, j * TILE_SIZE, i * TILE_SIZE, get_rgba(255, 255, 255, 1));
			j++;
		}
		i++;
	}
	// draw_grid();
	draw_player(&g_game->img_map, g_game->player.x, g_game->player.y, get_rgba(255, 0, 0, 1));
}


void DDA(mlx_image_t **img, float X0, float Y0, float X1, float Y1)
{
	int dx = X1 - X0;
	int dy = Y1 - Y0;
	int steps;

	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	float Xinc = dx / (float)steps;
	float Yinc = dy / (float)steps;
	float X = g_game->player.x;
	float Y = g_game->player.y;
	for (int i = 0; i <= steps; i++)
	{
		mlx_put_pixel(*img, X, Y, get_rgba(211, 100, 100, 3));
		X += Xinc;
		Y += Yinc;
	}
}
