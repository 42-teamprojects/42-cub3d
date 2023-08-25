/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelaissa <yelaissa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/25 14:39:27 by yelaissa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_fc(void)
{
	int i;
	int	j;
	
	i = 0;
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
		{
			mlx_put_pixel(g_game->img_map, i, j, \
			get_rgba(g_game->map->info->c[0], g_game->map->info->c[1], \
			g_game->map->info->c[2], 1));
			j++;
		}
		j = HEIGHT / 2;
		while (j < HEIGHT)
		{
			mlx_put_pixel(g_game->img_map, i, j, \
			get_rgba(g_game->map->info->f[0], g_game->map->info->f[1], \
			g_game->map->info->f[2], 1));
			j++;
		}
		i++;
	}
}

void	cast_ray(void)
{
	int		num_rays;
	float	ray_angle;
	t_ray	ray;
	t_cords	param;

	num_rays = WIDTH;
	ray_angle = g_game->player.angle - (g_game->player.fov / 2);
	draw_fc();
	param.x = 0;
	while (param.x < num_rays)
	{
		ray_angle += g_game->player.fov / num_rays;
		ray = get_ray(ray_angle);
		param.y = (HEIGHT / 2) - (ray.wall_height / 2);
		if (param.y < 0)
			param.y = 0;
		draw_texture(ray, param, ray.wall_height);
		param.x++;
	}
}

float	normalize_angle(float ray_angle)
{
	if (ray_angle < 0)
		ray_angle = (2 * M_PI) + ray_angle;
	else if (ray_angle > 2 * M_PI)
		ray_angle = ray_angle - (2 * M_PI);
	return (ray_angle);
}

int	check_wall(float x, float y)
{
	int		x1;
	int		y1;
	float	lenx;

	x1 = (int)x / TILE_SIZE;
	y1 = (int)y / TILE_SIZE;
	if (y1 >= g_game->map->height)
		return (1);
	lenx = ft_strlen(g_game->map->map[y1]);
	if (x1 < 0 || x1 >= lenx || y1 < 0 || y1 >= g_game->map->height)
		return (1);
	if (g_game->map->map[y1][x1] == '1')
		return (1);
	return (0);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
