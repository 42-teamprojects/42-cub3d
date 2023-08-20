/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/20 13:07:03 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	utils_catray(t_cords cords)
{
	int	j;

	while (cords.x < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
		{
			mlx_put_pixel(g_game->img_map, cords.x, j, \
			get_rgba(g_game->map->info->c[0], g_game->map->info->c[1], \
			g_game->map->info->c[2], 1));
			j++;
		}
		j = HEIGHT / 2;
		while (j < HEIGHT)
		{
			mlx_put_pixel(g_game->img_map, cords.x, j, \
			get_rgba(g_game->map->info->f[0], g_game->map->info->f[1], \
			g_game->map->info->f[2], 1));
			j++;
		}
		cords.x++;
	}
}

void	cast_ray(void)
{
	int		num_rays;
	float	ray_angle;
	t_ray	ray;
	int		j;
	t_cords	cords;

	num_rays = WIDTH;
	ray_angle = g_game->player.angle - (g_game->player.fov / 2);
	j = 0;
	cords.x = 0;
	utils_catray(cords);
	cords.x = 0;
	while (cords.x < num_rays)
	{
		ray_angle += g_game->player.fov / num_rays;
		ray = get_ray(ray_angle);
		cords.start = (HEIGHT / 2) - (ray.wall_height / 2);
		cords.end = ray.wall_height;
		if (cords.start < 0)
			cords.start = 0;
		cords.width = 1;
		cords.y = cords.start;
		rect(ray, cords, cords.end, get_rgba(255, 0, 0, 1));
		cords.x++;
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
