/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:18:23 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/16 08:29:38 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int get_rgba(int r, int g, int b, float a)
{
    int color;

    color = r << 24 | g << 16 | b << 8 | (int)a * 255;
    return (color);
}
void rect(t_ray ray, float x, float y, int width, int height, int color)
{
	(void) width;
	(void) color;
	(void) ray;
	float y_inc = (float)g_game->ea->height / (float)(height);
	int *pointer;
	int column; 
	if(ray.was_hit_vert)
	{
		column= (int)ray.wall_hit_y % TILE_SIZE;
		
		if(ray.is_left)
		{
			pointer = g_game->we_pxls;
			column = TILE_SIZE - column - 1;
		}
		else if(ray.is_right)
			pointer = g_game->ea_pxls;
	}
	else
	{
		column= (int)ray.wall_hit_x % TILE_SIZE;
		if(ray.is_up)
			pointer = g_game->no_pxls;
		else if(ray.is_down)
		{
			pointer = g_game->so_pxls;
			column = TILE_SIZE - column - 1;
		}
	}
	float w_err = height / 2 - HEIGHT / 2;
	if(w_err < 0)
		w_err = 0;
	float start = w_err * y_inc;
	uint32_t i = 0;
	while ((int)i < height && HEIGHT > (int)(i))
	{
		color = pointer[(int)column + (g_game->ea->width * (int)start)];
			mlx_put_pixel(g_game->img_map, x, y + i, color);
		start += y_inc;
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

// void	draw_grid()
// {
// 	float	x;
// 	float	y;
	
// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		y = 0;
// 		while (y < g_game->map->height * TILE_SIZE)
// 		{
// 			mlx_put_pixel(g_game->img_map, x, y, get_rgba(5, 15, 0, 1));
// 			y++;
// 		}
// 		x += TILE_SIZE;
// 	}
// 	y = 0;
// 	while (y < g_game->map->height * TILE_SIZE)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			mlx_put_pixel(g_game->img_map, x, y, get_rgba(5, 15, 0, 1));
// 			x++;
// 		}
// 		y += TILE_SIZE;
// 	}
// }


void	draw_player(mlx_image_t **img, float posx, float posy, int color)
{
	float	i;
	float	j;

	i = posx;
	while (i < (posx + (TILE_SIZE / 2)) )
	{
		j = posy;
		while (j < posy + (TILE_SIZE / 2) )
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
	while (g_game->map->map[i])
	{
		j = 0;
		while (g_game->map->map[i][j])
		{
			if (g_game->map->map[i][j] == '1')
				draw_pixels(&g_game->img_map, j * TILE_SIZE , i * TILE_SIZE, get_rgba(255, 255, 255, 1));
			j++;
		}
		i++;
	}
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
