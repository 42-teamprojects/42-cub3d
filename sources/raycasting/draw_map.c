/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:18:23 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/14 09:59:12 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b, float a)
{
	int	color;

	color = r << 24 | g << 16 | b << 8 | (int)a * 255;
	return (color);
}

void	rect(t_cords param, int width, int height, int color)
{
	int	i;
	int	j;

	i = param.x;
	while (i < param.x + width)
	{
		j = 0;
		while (height > param.y && HEIGHT > param.y)
		{
			mlx_put_pixel(g_game->img_map, param.x, param.y, color);
			param.y++;
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

void	draw_grid(void)
{
	float	x;
	float	y;

	x = 0;
	while (x < g_game->map->width * TILE_SIZE)
	{
		y = 0;
		while (y < g_game->map->height * TILE_SIZE)
		{
			mlx_put_pixel(g_game->img_map, x, y, get_rgba(5, 15, 0, 1));
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
			mlx_put_pixel(g_game->img_map, x, y, get_rgba(5, 15, 0, 1));
			x++;
		}
		y += TILE_SIZE;
	}
}

void	draw_player(mlx_image_t **img, float posx, float posy, int color)
{
	float	i;
	float	j;

	i = posx;
	while (i < (posx + (TILE_SIZE / 2)))
	{
		j = posy;
		while (j < posy + (TILE_SIZE / 2))
		{
			mlx_put_pixel(*img, i, j, color);
			j++;
		}
		i++;
	}
}
