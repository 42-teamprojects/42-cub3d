/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htalhaou <htalhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 10:05:26 by htalhaou          #+#    #+#             */
/*   Updated: 2023/08/20 13:07:17 by htalhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda(float x_x, float y_y, float x1, float y1)
{
	t_cords	d;
	int		steps;
	t_cords	inc;
	t_cords	p;
	int		i;

	d.x = x1 - x_x;
	d.y = y1 - y_y;
	if ((abs((int)d.x)) > (abs((int)d.y)))
		steps = (abs((int)d.x));
	else
		steps = (abs((int)d.y));
	inc.x = d.x / (float)steps;
	inc.y = d.y / (float)steps;
	p.x = g_game->player.x;
	p.y = g_game->player.y;
	i = 0;
	while (i <= steps)
	{
		mlx_put_pixel(g_game->img_map, p.x, p.y, get_rgba(211, 100, 100, 3));
		p.x += inc.x;
		p.y += inc.y;
		i++;
	}
}

void	draw_map(void)
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
				draw_pixels(&g_game->img_map, j * TILE_SIZE, i * TILE_SIZE \
					, get_rgba(255, 255, 255, 1));
			j++;
		}
		i++;
	}
	draw_player(&g_game->img_map, g_game->player.x, \
		g_game->player.y, get_rgba(255, 0, 0, 1));
}

t_ray	get_ray(float ray_angle)
{
	t_ray	h_ray;
	t_ray	v_ray;
	float	fish_eye_fix;

	h_ray = horizontal_ray_intersection(ray_angle);
	v_ray = vertical_ray_intersection(ray_angle);
	if (h_ray.was_hit)
		h_ray.distance = distance_between_points(g_game->player.x, \
		g_game->player.y, h_ray.wall_hit_x, h_ray.wall_hit_y);
	else
		h_ray.distance = INT_MAX;
	if (v_ray.was_hit)
		v_ray.distance = distance_between_points(g_game->player.x, \
		g_game->player.y, v_ray.wall_hit_x, v_ray.wall_hit_y);
	else
		v_ray.distance = INT_MAX;
	fish_eye_fix = cos(ray_angle - g_game->player.angle);
	h_ray.wall_height = (HEIGHT / (h_ray.distance * fish_eye_fix / TILE_SIZE));
	v_ray.wall_height = (HEIGHT / (v_ray.distance * fish_eye_fix / TILE_SIZE));
	if (h_ray.distance < v_ray.distance)
		return ((h_ray.was_hit_vert = 0), h_ray);
	else
		return ((v_ray.was_hit_vert = 1), v_ray);
}
