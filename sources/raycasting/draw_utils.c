/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:18:23 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/26 12:45:28 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

struct s_vars {
	float		y_inc;
	float		row;
	int			i;
	float		start;
	int			*tex_colors;
	int			column;
	int			color;	
};

void	find_texture(t_ray ray, int **tex_colors, int *column)
{
	if (ray.was_hit_vert)
	{
		*column = (int)ray.wall_hit_y % TILE_SIZE;
		if (ray.is_left)
		{
			*tex_colors = g_game->we_pxls;
			*column = TILE_SIZE - *column - 1;
		}
		else if (ray.is_right)
			*tex_colors = g_game->ea_pxls;
	}
	else
	{
		*column = (int)ray.wall_hit_x % TILE_SIZE;
		if (ray.is_up)
			*tex_colors = g_game->no_pxls;
		else if (ray.is_down)
		{
			*tex_colors = g_game->so_pxls;
			*column = TILE_SIZE - *column - 1;
		}
	}
}

void	draw_texture(t_ray ray, t_cords param, float wall_height)
{
	struct s_vars	*vars;

	vars = malloc(sizeof(struct s_vars));
	find_texture(ray, &vars->tex_colors, &vars->column);
	vars->y_inc = (float)TILE_SIZE / (float)(wall_height);
	vars->start = wall_height / 2 - HEIGHT / 2;
	if (vars->start < 0)
		vars->start = 0;
	vars->row = vars->start * vars->y_inc;
	vars->i = 0;
	while (vars->i < wall_height && HEIGHT > vars->i)
	{
		vars->color = vars->tex_colors[vars->column + \
			(TILE_SIZE * (int)vars->row)];
		mlx_put_pixel(g_game->img_map, param.x, param.y + vars->i, vars->color);
		vars->row += vars->y_inc;
		vars->i++;
	}
	free(vars);
}

int	get_rgba(int r, int g, int b, float a)
{
	int	color;

	color = r << 24 | g << 16 | b << 8 | (int)a * 255;
	return (color);
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
