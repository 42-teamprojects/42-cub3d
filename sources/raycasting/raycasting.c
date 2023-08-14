/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:44:43 by yelaissa          #+#    #+#             */
/*   Updated: 2023/08/14 15:41:10 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgba(int r, int g, int b, float a)
{
	int	alpha;

	alpha = (int)(a * 255);
	return (alpha << 24 | r << 16 | g << 8 | b);
}

void	cast_ray(void)
{
	int		num_rays;
	float	ray_angle;
	t_ray	ray;
	t_cords	rect_cords;

	num_rays = WIDTH;
	ray_angle = g_game->player.angle - (g_game->player.fov / 2);
	rect_cords.x = 0;
	draw_sky_and_floor(rect_cords);
	while (rect_cords.x < num_rays)
	{
		ray_angle += g_game->player.fov / num_rays;
		ray = get_ray(ray_angle);
		rect_cords.start = (HEIGHT / 2) - (ray.wall_height / 2);
		rect_cords.end = (HEIGHT / 2) + (ray.wall_height / 2);
		if (rect_cords.start < 0)
			rect_cords.start = 0;
		dda(g_game->player.x, g_game->player.y, ray.wall_hit_x, ray.wall_hit_y);
		rect_cords.y = rect_cords.start;
		rect(rect_cords, 1, rect_cords.end, get_rgba(255, 0, 0, 1));
		rect_cords.x++;
	}
}

void	draw_sky_and_floor(t_cords rect_cords)
{
	int	j;

	rect_cords.x = 0;
	while (rect_cords.x < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
		{
			mlx_put_pixel(g_game->img_map, rect_cords.x, j, \
				get_rgba(g_game->map->info->c[0], \
				g_game->map->info->c[1], g_game->map->info->c[2], 1));
			j++;
		}
		j = HEIGHT / 2;
		while (j < HEIGHT)
		{
			mlx_put_pixel(g_game->img_map, rect_cords.x, j, \
				get_rgba(g_game->map->info->f[0], \
				g_game->map->info->f[1], g_game->map->info->f[2], 1));
			j++;
		}
		rect_cords.x++;
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
	if (y1 > g_game->map->height)
		return (1);
	lenx = ft_strlen(g_game->map->map[y1]);
	if (x1 < 0 || x1 >= lenx || y1 < 0 || y1 >= g_game->map->height)
		return (1);
	if (g_game->map->map[y1][x1] == '1')
		return (1);
	return (0);
}
