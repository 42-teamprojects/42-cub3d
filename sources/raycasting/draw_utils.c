/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 10:18:23 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/25 18:25:07 by yelaissa         ###   ########.fr       */
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

// This function finds the texture to be used for the wall and the column of the texture to be used.
// It takes a ray, a pointer to an integer pointer to store the texture colors, and a pointer to an integer to store the column.
// It determines the column based on whether the ray hit a vertical or horizontal wall and which side of the wall it hit.
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

// This function draws the texture of the wall on the screen.
// It takes a ray, a t_cords struct containing the x and y coordinates of the wall, and the height of the wall.
// It first calls find_texture to determine which texture to use and which column of the texture to use.
// It then calculates the increment in y direction for each pixel of the wall and the starting pixel of the wall.
// It then loops through each pixel of the wall and puts the corresponding pixel of the texture on the screen.
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
		vars->color = vars->tex_colors[vars->column + (TILE_SIZE * (int)vars->row)];
		mlx_put_pixel(g_game->img_map, param.x, param.y + vars->i, vars->color);
		vars->row += vars->y_inc;
		vars->i++;
	}
	free(vars);
}

// This function returns an integer representing a color in RGBA format.
// It takes four integers representing the red, green, blue, and alpha values of the color.
int	get_rgba(int r, int g, int b, float a)
{
	int	color;

	color = r << 24 | g << 16 | b << 8 | (int)a * 255;
	return (color);
}

// This function draws a square of pixels on the screen.
// It takes a pointer to an mlx_image_t struct, the height and width of the square, and the color of the pixels.
// It loops through each pixel of the square and puts the corresponding color on the screen.
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
