/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:18:23 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/20 12:42:55 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_rgba(int r, int g, int b, float a)
{
	int	color;

	color = r << 24 | g << 16 | b << 8 | (int)a * 255;
	return (color);
}

void	utils_rect(t_ray ray, int **pointer, int *column)
{
	if (ray.was_hit_vert)
	{
		*column = (int)ray.wall_hit_y % TILE_SIZE;
		if (ray.is_left)
		{
			*pointer = g_game->we_pxls;
			*column = TILE_SIZE - *column - 1;
		}
		else if (ray.is_right)
			*pointer = g_game->ea_pxls;
	}
	else
	{
		*column = (int)ray.wall_hit_x % TILE_SIZE;
		if (ray.is_up)
			*pointer = g_game->no_pxls;
		else if (ray.is_down)
		{
			*pointer = g_game->so_pxls;
			*column = TILE_SIZE - *column - 1;
		}
	}
}

void	rect(t_ray ray, t_cords param, int height, int color)
{
	float		y_inc;
	int			i;
	float		w_err;
	int			column;
	int			*pointer;

	pointer = NULL;
	column = 0;
	y_inc = (float)g_game->ea->height / (float)(height);
	utils_rect(ray, &pointer, &column);
	w_err = height / 2 - HEIGHT / 2;
	if (w_err < 0)
	{
		w_err = 0;
	}
	param.start = w_err * y_inc;
	i = 0;
	while ((int)i < height && HEIGHT > (int)(i))
	{
		color = pointer[(int)column + (g_game->ea->width * (int)param.start)];
		mlx_put_pixel(g_game->img_map, param.x, param.y + i, color);
		param.start += y_inc;
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
